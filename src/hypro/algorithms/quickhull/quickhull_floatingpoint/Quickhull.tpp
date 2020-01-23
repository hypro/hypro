namespace hypro {
    template<typename Number, bool Euclidian>
    FloatQuickhull<Number, Euclidian>::Quickhull(pointVector_t& points, dimension_t dimension) 
    : points(points), dimension(dimension), fSpace(points, currentVertices, dimension) {}

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::compute() {

    
        for(auto& point : points) {
            TRACE("quickhull", point * (2 << 12));
        }

        removeDuplicateInputs();

        //In the case of halfspace intersection, this does not occur unless the input is invalid,
        //since a single halfspace always defines an open set.
        if constexpr(Euclidian) {
            //There's only a single point, so we fix it from both sides.
            if(dimension == 1 && points.size() == 1) {
                makeTrivialHull();
                return;
            }
        }

        buildInitialPolytope();
        
        for(Facet& facet : fSpace.facets) {
            TRACE("quickhull", "furthest " << facet.furthestPoint << std::endl << " distance " << facet.furthestPointDistance);
        }
        
        processPoints();
#ifndef NDEBUG        
        TRACE("quickhull", "ALL facets:" << std::endl << fSpace.printAll());
#endif

        fSpace.compressVector();
        fSpace.removeCoplanarFacets();

#ifndef NDEBUG
        TRACE("quickhull", "ALL facets:" << std::endl << fSpace.printAll());

        for(facet_ind_t facet_i = 0; facet_i < fSpace.facets.size(); ++facet_i) {
            Facet& facet = fSpace.facets[facet_i];
            for(point_ind_t point_i = 0; point_i < points.size(); ++point_i) {
                point_t point = points[point_i];
                if(facet.visible(point)) {
                    TRACE("quickhull", "NON CONTAINMENT" << std::endl << point << std::endl << "Facet:" << std::endl << fSpace.printFacet(facet));
                    TRACE("quickhull", "facet_i: " << facet_i);
                    TRACE("quickhull", "distance" << std::endl << facet.distance(point));
                    assert(false);
                }
            }
        }
#endif
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::removeDuplicateInputs() {
        for(point_ind_t point_i = 0; point_i < points.size(); ++point_i) {
            for(point_ind_t point_j = point_i + 1; point_j < points.size(); ++point_j) {
                if(points[point_i] == points[point_j]) {
                    points.erase(points.begin() + point_j);
                }
            }
        }
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::makeTrivialHull() {
        fSpace.insertTrivialFacet(points[0][0]);
        fSpace.insertTrivialFacet(points[0][0]);
        fSpace.facets.back().invert();
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::buildInitialPolytope() {

        if(constructInitialFacet()) return;

        //Find furthest away point
        auto [onPlane, furthestPoint_i] = findFurthestPoint(fSpace.facets.back());

        TRACE("quickhull", "onPlane " << onPlane << " furthestPoint_i " << furthestPoint_i);

        //Since the number type is exact, check if the furthest away point is on the inital facet.
        if(onPlane) {
            constructLowerDimensional();
            return;
        }

        currentVertices.push_back(furthestPoint_i);

        //Set orientation
        if(fSpace.facets.front().visible(points[furthestPoint_i])) {
            fSpace.facets.front().invert();
        }
        
        fSpace.endModificationPhase();

        //Create cone from the new point
        for(size_t i = 0; i < dimension; ++i) {
            Facet& createdFacet = fSpace.insertNew();
            size_t insertedAt = fSpace.copyVertices(createdFacet, fSpace.facets[0], furthestPoint_i, i);
            fSpace.computeNormal(createdFacet);
            if(!fSpace.validateFacet(createdFacet)) {
                fSpace.facets.pop_back();
                constructLowerDimensional();
                return;
            }

            //Set i-th neighbor of initial facet to the created facet.
            fSpace.facets.front().mNeighbors[i] = fSpace.facets.size() - 1; 
            
            for(facet_ind_t other_i = 0; other_i < fSpace.facets.size() - 1; ++other_i ) {
                if constexpr(Euclidian) {
                    assert(fSpace.facets[other_i].mNormal != createdFacet.mNormal);
                } else {
                    assert(fSpace.facets[other_i].mNormal != createdFacet.mNormal ||
                     fSpace.facets[other_i].offset() != createdFacet.offset());
                }
            }
            
            createdFacet.mNeighbors[insertedAt] = 0;
            findConeNeighbors(fSpace.facets.size() - 1);
        }

        initialPartition();

        fSpace.endModificationPhase();
    }

    template<typename Number, bool Euclidian>
    bool FloatQuickhull<Number, Euclidian>::constructInitialFacet() {
        Facet& facet = fSpace.insertNew();

        Eigen::FullPivLU<matrix_t<Number>> lu(dimension, dimension + 1);
        matrix_t<Number> matrix = matrix_t<Number>::Zero(dimension, dimension + 1);

        //Do first iteration
        facet.mVertices[0] = 0;
        currentVertices.push_back(0);

        //Set the first row
        if constexpr(Euclidian) {
            matrix.row(0).head(dimension) = points[0].transpose();
            matrix(0, dimension) = 1;
        } else {
            matrix.row(0) = points[0].transpose();
        }

        //Compute normal and offset
        lu.compute(matrix);
        vector_t<Number> result = lu.kernel().col(0);

        facet.mNormal = result.head(dimension);
        fSpace.fixOffset(facet);

        for(size_t d = 1; d < dimension; ++d) {
            auto [onPlane, furthestPoint_i] = findFurthestPoint(facet);

            if(onPlane) {
                constructLowerDimensional();
                return true;
            }

            facet.mVertices[d] = furthestPoint_i;
            currentVertices.push_back(furthestPoint_i);
            //Set the (d+1)-th row
            if constexpr(Euclidian) {
                matrix.row(d).head(dimension) = points[furthestPoint_i].transpose();
                matrix(d, dimension) = 1;
            } else {
                matrix.row(d) = points[furthestPoint_i].transpose();
            }
            
            //Compute normal and offset
            lu.compute(matrix);
            result = lu.kernel().col(0);

            facet.mNormal = result.head(dimension);
            fSpace.fixOffset(facet);
        }
        std::sort(facet.mVertices.begin(), facet.mVertices.end());

        return false;
    }

    template<typename Number, bool Euclidian>
    std::tuple<bool, size_t> FloatQuickhull<Number, Euclidian>::findFurthestPoint(Facet& facet) {
        point_ind_t furthestPoint = 0;
        Number furthestDistance = 0;

        for(point_ind_t point_i = 0; point_i < points.size(); ++point_i) {
            double distanceLeft = facet.template outerDistance<FE_DOWNWARD>(points[point_i]);
            double distanceRight = -facet.template innerDistance<FE_UPWARD>(points[point_i]);

            double distance = std::max<Number>(std::max<Number>(distanceLeft, 0), distanceRight);
            
            if constexpr(!Euclidian) {
                if(distance > 0 && points[point_i][dimension] == 0) {
                    return std::make_tuple(false, point_i);
                }
            }

            if(distance > furthestDistance) {
                furthestDistance = distance;
                furthestPoint = point_i;
            }
        }

        return std::make_tuple(furthestDistance == 0, furthestPoint);
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::processPoints() {

        facet_ind_t facetToProcess_i = getFacetToProcess();

        while(facetToProcess_i != fSpace.facets.size()) {

            currentVertices.push_back(fSpace.facets[facetToProcess_i].furthestPoint);

            bitset_t visited{fSpace.facets.size()};
            visited.set(facetToProcess_i);
            buildCone(facetToProcess_i, fSpace.facets[facetToProcess_i].furthestPoint, visited);

            partitionAllVertices(fSpace.facets[facetToProcess_i].furthestPoint);
            fSpace.endModificationPhase();

            facetToProcess_i = getFacetToProcess();
        }
    }

    template<typename Number, bool Euclidian>
    typename FloatQuickhull<Number, Euclidian>::facet_ind_t FloatQuickhull<Number, Euclidian>::getFacetToProcess() {
        return fSpace.findFacet([](Facet& facet) {
            return !facet.mOutsideSet.empty();
        });
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::buildCone(facet_ind_t currentFacet_i, point_ind_t visiblePoint_i, bitset_t& visited) {
        fSpace.deleteFacet(currentFacet_i);

        point_t& visiblePoint = points[visiblePoint_i];

        for(size_t neighbor_pos = 0; neighbor_pos < dimension; ++neighbor_pos) {
            facet_ind_t neighbor_i = fSpace.facets[currentFacet_i].mNeighbors[neighbor_pos];

            if(!visited[neighbor_i]) {
                //neighbor is "inside" horizon
                if(fSpace.facets[neighbor_i].innerVisible(visiblePoint)) {
                    visited.set(neighbor_i);
                    buildCone(neighbor_i, visiblePoint_i, visited);
                } else {
                    //this ridge to the neighbor is part of the horizon
                    
                    //Find the index of the ridge from the facet outside the horizon (neighbor_i) to the facet inside the horizon (currentFacet_i).
                    size_t ridgeIndex_outer_inner = fSpace.facets[neighbor_i].findNeighborIndex(currentFacet_i);

                    Facet& createdFacet = fSpace.insertNew();
                    size_t differentiatingPosition = fSpace.copyVertices(createdFacet, fSpace.facets[neighbor_i], visiblePoint_i, ridgeIndex_outer_inner);
                    fSpace.computeNormal(createdFacet);
                    if(!fSpace.validateFacet(createdFacet)) {
                        fSpace.facets.resize(1);
                        constructLowerDimensional();
                        fSpace.deletedPositions.clear();
                        return;
                        static_assert(false);
                    }
#ifndef NDEBUG
                    fSpace.containsAllPoints(fSpace.facets.back());
#endif
                    //Set the outside facet as neighbor of the new facet at the index where the differentiating point was inserted.
                    fSpace.facets.back().mNeighbors[differentiatingPosition] = neighbor_i;
                    //Replace the facet inside the horizon (currentFacet_i) as neighbor of neighbor_i with the newly created facet.
                    fSpace.facets[neighbor_i].mNeighbors[ridgeIndex_outer_inner] = fSpace.facets.size() - 1 /*The index of the new facet*/;

                    findConeNeighbors(fSpace.facets.size() - 1);
                }
            }
        }
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::constructLowerDimensional() {

        if constexpr(!Euclidian) {
            //This means that a single point lies on all given halfspaces.
            //For this to be valid (their intersection not to be open), they must be linearly independent.
            //TODO check for this properly
            return;
        }

        //TODO
        //Needs fixing for inexact arithmetic
        assert(false);

        TRACE("quickhull", "dropping from d=" << dimension << " to d=" << dimension - 1);

        //Copy first facet
        fSpace.facets.push_back(fSpace.facets.front());
        fSpace.facets.back().invert();

        fSpace.facets.front().mOuterOffset = 
            std::accumulate(points.begin(), points.end(), -std::numeric_limits<Number>::infinity(), [this](Number& prev, point_t& point) {
                return std::max(prev, point.dot(fSpace.facets.front().mNormal));
            });

        fSpace.facets.back().mOuterOffset = 
            std::accumulate(points.begin(), points.end(), -std::numeric_limits<Number>::infinity(), [this](Number& prev, point_t& point) {
                return std::max(prev, point.dot(fSpace.facets.back().mNormal));
            });
    
        size_t reducableDimension = 0;
        for(; reducableDimension < dimension; ++reducableDimension) {
            if(fSpace.facets.front().mNormal[reducableDimension] != 0) break;
        }

        assert(fSpace.facets.front().mNormal != point_t::Zero(dimension));
        assert(reducableDimension < dimension);

        pointVector_t reducedPoints;

        std::transform(points.begin(), points.end(), std::back_inserter<pointVector_t>(reducedPoints), [reducableDimension, this](point_t& point) {            
            point_t reducedPoint{pointSize() - 1};

            for(size_t i=0,j=0; i < pointSize() - 1; ++i,++j) {
                if(j == reducableDimension) j += 1;
                reducedPoint[i] = point[j];
            }

            //Should be RVO'd
            return reducedPoint;
        });

        //TODO I have no idea how the 'Euclidian' template argument of Quickhull is inferred here.
        Quickhull qh{reducedPoints, dimension - 1};
        static_assert(std::is_same_v<decltype(qh), FloatQuickhull<Number, Euclidian>>);

        qh.compute();

        for(Facet const& facet : qh.getFacets()) {
            fSpace.insertReduced(facet, pointSize(), reducableDimension);
        }
    }

  
    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::findConeNeighbors(facet_ind_t facet_i) {
        //We always ignore the last one
        for(facet_ind_t inserted_i = fSpace.firstInserted; inserted_i < fSpace.facets.size() - 1; ++inserted_i) {
            fSpace.establishNeighborhood(facet_i, inserted_i);
        }
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::partitionAllVertices(point_ind_t newVertex_i) {

        for(facet_ind_t deleted_i : fSpace.deletedPositions) {

            for(point_ind_t outside_i : fSpace.facets[deleted_i].mOutsideSet) {
                if(outside_i == newVertex_i) continue;
                for(facet_ind_t inserted_i = fSpace.firstInserted; inserted_i < fSpace.facets.size(); ++inserted_i) {
                   if(fSpace.tryAddToOutsideSet(fSpace.facets[inserted_i], outside_i)) break;
                }
            }

            fSpace.facets[deleted_i].mOutsideSet.clear();
        }
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::initialPartition() {
        for(point_ind_t point_i = 0; point_i < points.size(); ++point_i) {
            if(std::find(currentVertices.begin(), currentVertices.end(), point_i) != currentVertices.end()) continue;
            for(Facet& facet : fSpace.facets) {
                if(fSpace.tryAddToOutsideSet(facet, point_i)) break;
            }
        }
    }

    template<typename Number, bool Euclidian>
    typename FloatQuickhull<Number, Euclidian>::facetVector_t& FloatQuickhull<Number, Euclidian>::getFacets() {
        return fSpace.facets;
    }

    template<typename Number, bool Euclidian>
    size_t FloatQuickhull<Number, Euclidian>::pointSize() {
        if constexpr(Euclidian) {
            return dimension;
        } else {
            return dimension + 1;
        }
    }
}
