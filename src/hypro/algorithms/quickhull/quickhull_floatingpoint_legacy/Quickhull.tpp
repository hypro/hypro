#include "Quickhull.h"

namespace hypro {
    template<typename Number>
    FloatQuickhull<Number>::Quickhull(pointVector_t& inputPoints, size_t dim) : inputPoints(inputPoints), dimension(dim), fSpace(inputPoints, dimension) {
    }

    template<typename Number>
    void FloatQuickhull<Number>::compute() {

#ifndef NDEBUG
        std::cout << "Inputs" << std::endl;
        std::cout << inputPoints << std::endl;
#endif
        removeDuplicateInputs();
        
        //There's only a single point, so we fix it from both sides.
        if(dimension == 1 && inputPoints.size() == 1) {
            makeTrivialHull();
            return;
        }

        buildInitialPolytope();
        processPoints();

        TRACE("quickhull", "ALL facets:" << std::endl << fSpace.printAll());

        fSpace.compressVector();

#ifndef NDEBUG
        TRACE("quickhull", "ALL facets:" << std::endl << fSpace.printAll());
        
        for(facet_ind_t facet_i = 0; facet_i < fSpace.facets.size(); ++facet_i) {
            Facet& facet = fSpace.facets[facet_i];
            for(point_t& point : inputPoints) {
                if(facet.visibleOuter(point)) {
                    TRACE("quickhull", "NON CONTAINMENT" << std::endl << point << std::endl << "Facet:" << std::endl << fSpace.printFacet(facet));
                    TRACE("quickhull", "facet_i: " << facet_i);
                    assert(false);
                }
            }
        }
#endif
    }

    template<typename Number>
    void FloatQuickhull<Number>::removeDuplicateInputs() {

        for(point_ind_t point_i = 0; point_i < inputPoints.size(); ++point_i) {
            for(point_ind_t point_j = point_i + 1; point_j < inputPoints.size(); ++point_j) {
                if(inputPoints[point_i] == inputPoints[point_j]) {
                    inputPoints.erase(inputPoints.begin() + point_j);
                }
            }
        }
    }

    template<typename Number>
    void FloatQuickhull<Number>::makeTrivialHull() {
        fSpace.insertTrivialFacet(inputPoints[0][0]);
        fSpace.insertTrivialFacet(inputPoints[0][0]);
        fSpace.facets.back().invert();
    }

    template<typename Number>
    void FloatQuickhull<Number>::buildInitialPolytope() {

        constructInitialFacet();

        if(inputPoints.size() < dimension + 1) {
            constructLowerDimensional();
            return;
        }

        //Find furthest away point
        auto [furthestDistance, furthestPoint_i] = findFurthestFromInitial();

        //If the number type is exact, check if the furthest away point is on the inital facet.
        if constexpr (is_exact<Number>) {
            if(furthestDistance == 0) {
                constructLowerDimensional();
                return;
            }
        }

        //calculate barycenter of initial polytope, which is the baryCenter of the first [1, ..., dim] points and the furthest away point
        baryCenter = inputPoints[furthestPoint_i].template cast<mpq_class>();

        for(size_t vertexInd = 0; vertexInd < dimension; ++vertexInd) {
            baryCenter += inputPoints[vertexInd].template cast<mpq_class>();
        }

        baryCenter /= dimension + 1;

        //Set orientation using the baryCenter and validate point containment for the initial facet.
        fSpace.facets.front().setOrientation(baryCenter);
        fSpace.validateVertexContainment(fSpace.facets.front());

        //
        fSpace.endModificationPhase();

        //Create cone from the new point
        for(size_t i = 0; i < dimension; ++i) {
            size_t insertedAt = fSpace.insertConePart(0, furthestPoint_i, i, baryCenter);
            Facet& createdFacet = fSpace.facets.back();

            if constexpr (!is_exact<Number>) {
                if(std::any_of(fSpace.facets.begin(), fSpace.facets.end() - 1, [createdFacet, this](Facet const& other){
                    return fSpace.isParallel(createdFacet, other);
                })) {
                    fSpace.facets.resize(1);
                    constructLowerDimensional();
                    return;
                }
            }

            fSpace.facets.front().mNeighbors[i] = fSpace.facets.size() - 1; //Set i-th neighbor of initial facet to the created facet.
            createdFacet.mNeighbors[insertedAt] = 0;
            findConeNeighbors(fSpace.facets.size() - 1);
        }

        initialPartition();

        fSpace.endModificationPhase();
    }

    template<typename Number>
    void FloatQuickhull<Number>::constructInitialFacet() {
        fSpace.insertNew();

        //Initialize the vertices of the initial facet to [1, ... ,dim]
        for(size_t i = 0; i < dimension && i < inputPoints.size(); ++i) {
            fSpace.facets.front().mVertices[i] = i;
        }

        fSpace.computeNormal(fSpace.facets.back());
    }

    template<typename Number>
    std::tuple<Number, size_t/*aka point_ind_t*/> FloatQuickhull<Number>::findFurthestFromInitial() {
        point_ind_t furthestPoint = 0;
        Number furthestDistance = 0;

        //Start from dimension to only consider points that the initial facet was not constructed from.
        for(point_ind_t point_i = dimension; point_i < inputPoints.size(); ++point_i) {
            Number distance = carl::abs(fSpace.facets.front().distance(inputPoints[point_i]));
            if(distance > furthestDistance) {
                furthestDistance = distance;
                furthestPoint = point_i;
            }
        }

        return std::make_tuple(furthestDistance, furthestPoint);
    }

    template<typename Number>
    void FloatQuickhull<Number>::processPoints() {

        size_t facetToProcess = getFacetToProcess();

        while(facetToProcess != fSpace.facets.size()) {

            bitset_t visited{fSpace.facets.size()};
            visited.set(facetToProcess);
            buildCone(facetToProcess, fSpace.facets[facetToProcess].furthestPoint, visited);

            partitionAllVertices();
            fSpace.endModificationPhase();

            facetToProcess = getFacetToProcess();
        }
    }

    template<typename Number>
    typename FloatQuickhull<Number>::facet_ind_t FloatQuickhull<Number>::getFacetToProcess() {
        return fSpace.findFacet([](Facet& facet) {
            return !facet.mOutsideSet.empty();
        });
    }

    template<typename Number>
    void FloatQuickhull<Number>::buildCone(facet_ind_t currentFacet_i, point_ind_t visiblePoint_i, bitset_t& visited) {
        fSpace.deleteFacet(currentFacet_i);

        point_t& visiblePoint = inputPoints[visiblePoint_i];

        for(size_t neighbor_pos = 0; neighbor_pos < dimension; ++neighbor_pos) {
            facet_ind_t neighbor_i = fSpace.facets[currentFacet_i].mNeighbors[neighbor_pos];

            if(!visited[neighbor_i]) {
                //neighbor is "inside" horizon
                if(fSpace.facets[neighbor_i].visibleInner(visiblePoint)) {
                    visited.set(neighbor_i);
                    buildCone(neighbor_i, visiblePoint_i, visited);
                } else {
                    //this ridge to the neighbor is part of the horizon
                    
                    //Find the index of the ridge from the facet outside the horizon (neighbor_i) to the facet inside the horizon (currentFacet_i).
                    size_t ridgeIndex_outer_inner = fSpace.facets[neighbor_i].findNeighborIndex(currentFacet_i);

                    size_t differentiatingPosition = fSpace.insertConePart(neighbor_i, visiblePoint_i, ridgeIndex_outer_inner, baryCenter);
                    
                    //Check if the new facet is convex to the one it was created from
                    if(fSpace.facets.back().visibleInner(inputPoints[fSpace.facets[neighbor_i].mVertices[ridgeIndex_outer_inner]]) ) {
                        //Not convex
                        fSpace.facets.back().mNormal = fSpace.facets[neighbor_i].mNormal;
                        fSpace.facets.back().mOuterOffset = fSpace.facets[neighbor_i].mOuterOffset;
                        fSpace.facets.back().mInnerOffset = fSpace.facets[neighbor_i].mInnerOffset;

                        fSpace.validateVertexContainment(fSpace.facets.back());

                        //idiot test
                        assert(fSpace.facets.back().visibleInner(inputPoints[fSpace.facets[neighbor_i].mVertices[ridgeIndex_outer_inner]]));
                        assert(!fSpace.facets.back().visibleInner(visiblePoint));
                    }

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
    void FloatQuickhull<Number>::constructLowerDimensional() {
        TRACE("quickhull", "dropping from d=" << dimension << " to d=" << dimension - 1);

        //Copy first facet
        fSpace.facets.push_back(fSpace.facets.front());
        fSpace.facets.back().invert();

        fSpace.validateVertexContainment(fSpace.facets.front());
        fSpace.validateVertexContainment(fSpace.facets.back());

        size_t reducableDimension = 0;
        for(; reducableDimension < dimension; ++reducableDimension) {
            if(fSpace.facets.front().mNormal[reducableDimension] != 0) break;
        }

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
    void FloatQuickhull<Number>::findConeNeighbors(facet_ind_t facet_i) {
        //We always ignore the last one
        for(facet_ind_t inserted_i = fSpace.firstInserted; inserted_i < fSpace.facets.size() - 1; ++inserted_i) {
            fSpace.establishNeighborhood(facet_i, inserted_i);
        }
    }

    template<typename Number>
    void FloatQuickhull<Number>::partitionAllVertices() {

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
    void FloatQuickhull<Number>::initialPartition() {
        for(point_ind_t point_i = 0; point_i < inputPoints.size(); ++point_i) {
            for(Facet& facet : fSpace.facets) {
                if(fSpace.tryAddToOutsideSet(facet, point_i)) break;
            }
        }
    }

    template<typename Number>
    typename FloatQuickhull<Number>::facetVector_t& FloatQuickhull<Number>::getFacets() {
        return fSpace.facets;
    }
}
