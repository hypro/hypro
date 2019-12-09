namespace hypro {
    template<typename Number>
    ExactQuickhull<Number>::Quickhull(pointVector_t& inputPoints, size_t dim) : inputPoints(inputPoints), dimension(dim), fSpace(inputPoints, dimension) {
    }

    template<typename Number>
    void ExactQuickhull<Number>::compute() {

        removeDuplicateInputs();

        //There's only a single point, so we fix it from both sides.
        if(dimension == 1 && inputPoints.size() == 1) {
            makeTrivialHull();
            return;
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
            for(point_ind_t point_i = 0; point_i < inputPoints.size(); ++point_i) {
                point_t point = inputPoints[point_i];
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

    template<typename Number>
    void ExactQuickhull<Number>::removeDuplicateInputs() {

        for(point_ind_t point_i = 0; point_i < inputPoints.size(); ++point_i) {
            for(point_ind_t point_j = point_i + 1; point_j < inputPoints.size(); ++point_j) {
                if(inputPoints[point_i] == inputPoints[point_j]) {
                    inputPoints.erase(inputPoints.begin() + point_j);
                }
            }
        }
    }

    template<typename Number>
    void ExactQuickhull<Number>::makeTrivialHull() {
        fSpace.insertTrivialFacet(inputPoints[0][0]);
        fSpace.insertTrivialFacet(inputPoints[0][0]);
        fSpace.facets.back().invert();
    }

    template<typename Number>
    void ExactQuickhull<Number>::buildInitialPolytope() {

        if(constructInitialFacet()) return;

        //Find furthest away point
        auto [furthestDistance, furthestPoint_i] = findFurthestPoint(fSpace.facets.back());

        TRACE("quickhull", "furthestDistance " << furthestDistance << " furthestPoint_i " << furthestPoint_i);

        //Since the number type is exact, check if the furthest away point is on the inital facet.
        if(furthestDistance == 0) {
            constructLowerDimensional();
            return;
        }

        //calculate barycenter of initial polytope, which is the baryCenter vertices of the initial facet and the furthest away point
        baryCenter = inputPoints[furthestPoint_i];

        for(size_t vertexPos = 0; vertexPos < dimension; ++vertexPos) {
            baryCenter += inputPoints[fSpace.facets.back().mVertices[vertexPos]];
        }

        baryCenter /= dimension + 1;

        //Set orientation
        fSpace.facets.front().setOrientation(baryCenter);
        
        fSpace.endModificationPhase();

        //Create cone from the new point
        for(size_t i = 0; i < dimension; ++i) {
            size_t insertedAt = fSpace.insertConePart(0, furthestPoint_i, i, baryCenter);
            Facet& createdFacet = fSpace.facets.back();

            fSpace.facets.front().mNeighbors[i] = fSpace.facets.size() - 1; //Set i-th neighbor of initial facet to the created facet.
            
            for(facet_ind_t other_i = 0; other_i < fSpace.facets.size() - 1; ++other_i ) {
                assert(fSpace.facets[other_i].mNormal != createdFacet.mNormal);
            }
            
            createdFacet.mNeighbors[insertedAt] = 0;
            findConeNeighbors(fSpace.facets.size() - 1);
        }

        initialPartition();

        fSpace.endModificationPhase();
    }

    template<typename Number>
    bool ExactQuickhull<Number>::constructInitialFacet() {
        Facet& facet = fSpace.insertNew();

        Eigen::FullPivLU<matrix_t<Number>> lu(dimension, dimension + 1);
        matrix_t<Number> matrix = matrix_t<Number>::Zero(dimension, dimension + 1);


        //Do first iteration
        facet.mVertices[0] = 0;
        //Set the first row
        matrix.block(0, 0, 1, dimension) = inputPoints[0].transpose();
        matrix(0, dimension) = 1;
        
        //Compute normal and offset
        lu.compute(matrix);
        vector_t<Number> result = lu.kernel().col(0);

        facet.mNormal = result.head(dimension);
        facet.mOffset = -result[dimension];

        for(size_t d = 1; d < dimension; ++d) {
            
            matrix_t<double> m = convert<mpq_class, double>(matrix);
            TRACE("quickhull", "matrix" <<  std::endl << m);

            vector_t<double> r = convert<mpq_class, double>(result);
            TRACE("quickhull", "result" << std::endl << r);

            auto [furthestDistance, furthestPoint_i] = findFurthestPoint(facet);

            if(furthestDistance == 0) {

                vector_t<double> v = convert<mpq_class, double>(fSpace.facets.front().mNormal);
                TRACE("quickhull", "normal " << v);

                constructLowerDimensional();
                return true;
            }

            facet.mVertices[d] = furthestPoint_i;
            //Set the (d+1)-th row
            matrix.block(d, 0, 1, dimension) = inputPoints[furthestPoint_i].transpose();
            matrix(d, dimension) = 1;

            //Compute normal and offset
            lu.compute(matrix);
            result = lu.kernel().col(0);

            facet.mNormal = result.head(dimension);
            facet.mOffset = -result[dimension];
        }

        matrix_t<double> m = convert<mpq_class, double>(matrix);
        TRACE("quickhull", "matrix" <<  std::endl << m);

        vector_t<double> r = convert<mpq_class, double>(result);
        TRACE("quickhull", "result" << std::endl << r);

        std::sort(facet.mVertices.begin(), facet.mVertices.end());

        return false;
    }

    template<typename Number>
    std::tuple<Number, size_t/*aka point_ind_t*/> ExactQuickhull<Number>::findFurthestPoint(Facet& facet) {
        point_ind_t furthestPoint = 0;
        Number furthestDistance = 0;

        for(point_ind_t point_i = 0; point_i < inputPoints.size(); ++point_i) {
            Number distance = carl::abs(facet.distance(inputPoints[point_i]));
            if(distance > furthestDistance) {
                furthestDistance = distance;
                furthestPoint = point_i;
            }
        }

        return std::make_tuple(furthestDistance, furthestPoint);
    }

    template<typename Number>
    void ExactQuickhull<Number>::processPoints() {

        facet_ind_t facetToProcess_i = getFacetToProcess();

        while(facetToProcess_i != fSpace.facets.size()) {

            bitset_t visited{fSpace.facets.size()};
            visited.set(facetToProcess_i);
            buildCone(facetToProcess_i, fSpace.facets[facetToProcess_i].furthestPoint, visited);

            partitionAllVertices();
            fSpace.endModificationPhase();

            facetToProcess_i = getFacetToProcess();
        }
    }

    template<typename Number>
    typename ExactQuickhull<Number>::facet_ind_t ExactQuickhull<Number>::getFacetToProcess() {
        return fSpace.findFacet([](Facet& facet) {
            return !facet.mOutsideSet.empty();
        });
    }

    template<typename Number>
    void ExactQuickhull<Number>::buildCone(facet_ind_t currentFacet_i, point_ind_t visiblePoint_i, bitset_t& visited) {
        fSpace.deleteFacet(currentFacet_i);

        point_t& visiblePoint = inputPoints[visiblePoint_i];

        for(size_t neighbor_pos = 0; neighbor_pos < dimension; ++neighbor_pos) {
            facet_ind_t neighbor_i = fSpace.facets[currentFacet_i].mNeighbors[neighbor_pos];

            if(!visited[neighbor_i]) {
                //neighbor is "inside" horizon
                if(fSpace.facets[neighbor_i].visible(visiblePoint)) {
                    visited.set(neighbor_i);
                    buildCone(neighbor_i, visiblePoint_i, visited);
                } else {
                    //this ridge to the neighbor is part of the horizon
                    
                    //Find the index of the ridge from the facet outside the horizon (neighbor_i) to the facet inside the horizon (currentFacet_i).
                    size_t ridgeIndex_outer_inner = fSpace.facets[neighbor_i].findNeighborIndex(currentFacet_i);

                    size_t differentiatingPosition = fSpace.insertConePart(neighbor_i, visiblePoint_i, ridgeIndex_outer_inner, baryCenter);
                    
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

    template<typename Number>
    void ExactQuickhull<Number>::constructLowerDimensional() {
        TRACE("quickhull", "dropping from d=" << dimension << " to d=" << dimension - 1);

        //Copy first facet
        fSpace.facets.push_back(fSpace.facets.front());
        fSpace.facets.back().invert();
    
        size_t reducableDimension = 0;
        for(; reducableDimension < dimension; ++reducableDimension) {
            if(fSpace.facets.front().mNormal[reducableDimension] != Number(0)) break;
        }

        vector_t<double> v = convert<mpq_class, double>(fSpace.facets.front().mNormal);
        TRACE("quickhull", "normal " << v);
        assert(fSpace.facets.front().mNormal != point_t::Zero(dimension));
        assert(reducableDimension < dimension);

        pointVector_t reducedPoints;

        std::transform(inputPoints.begin(), inputPoints.end(), std::back_inserter<pointVector_t>(reducedPoints), [reducableDimension, this](point_t& point) {
            point_t reducedPoint{dimension - 1};

            for(size_t i=0,j=0; i < dimension - 1; ++i,++j) {
                if(j == reducableDimension) j += 1;
                reducedPoint[i] = point[j];
            }

            //Should be RVO'd
            return reducedPoint;
        });


        Quickhull qh{reducedPoints, dimension - 1};
        qh.compute();

        for(Facet const& facet : qh.getFacets()) {
            fSpace.insertReduced(facet, dimension, reducableDimension);
        }
    }


    template<typename Number>
    void ExactQuickhull<Number>::findConeNeighbors(facet_ind_t facet_i) {
        //We always ignore the last one
        for(facet_ind_t inserted_i = fSpace.firstInserted; inserted_i < fSpace.facets.size() - 1; ++inserted_i) {
            fSpace.establishNeighborhood(facet_i, inserted_i);
        }
    }

    template<typename Number>
    void ExactQuickhull<Number>::partitionAllVertices() {

        for(facet_ind_t deleted_i : fSpace.deletedPositions) {

            for(point_ind_t outside_i : fSpace.facets[deleted_i].mOutsideSet) {

                for(facet_ind_t inserted_i = fSpace.firstInserted; inserted_i < fSpace.facets.size(); ++inserted_i) {
                   if(fSpace.tryAddToOutsideSet(fSpace.facets[inserted_i], outside_i)) break;
                }

            }

            fSpace.facets[deleted_i].mOutsideSet.clear();
        }
    }

    template<typename Number>
    void ExactQuickhull<Number>::initialPartition() {
        for(point_ind_t point_i = 0; point_i < inputPoints.size(); ++point_i) {
            for(Facet& facet : fSpace.facets) {
                if(fSpace.tryAddToOutsideSet(facet, point_i)) break;
            }
        }
    }

    template<typename Number>
    typename ExactQuickhull<Number>::facetVector_t& ExactQuickhull<Number>::getFacets() {
        return fSpace.facets;
    }
}
