/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Leaf.h
 *
 * A RootGrowNode that represents a leaf node in the tree of operations representing a SupportFunction.
 * Each tree has a pointer to a Representation: Box, H-Polytope, etc.
 *
 * @author Stefan Schupp
 * @author Phillip Tse
 */

#pragma once

#include "../../types.h"

namespace hypro {

    template<typename Number, typename Converter, typename Setting>
    class RootGrowNode;

// A data struct for leaves, containing all needed info to construct a leaf from it
// The infos are the address to the representation as an actual number and the type of the representation.
    struct LeafData : public RGNData {
        uintptr_t addressToRep;
        representation_name typeOfRep = representation_name::UNDEF;
        bool isNotRedundant;

        LeafData() {};

        LeafData(const uintptr_t addr, const representation_name rep, const bool redundancy)
                : addressToRep(addr), typeOfRep(rep), isNotRedundant(redundancy) {}
    };

// Subclass of RootGrowNode, is a node with a representation of a state
    template<typename Number, typename Converter, typename Setting, typename Representation>
    class Leaf : public RootGrowNode<Number, Converter, Setting> {
    private:
        ////// General Interface

        SFNEW_TYPE type = SFNEW_TYPE::LEAF;
        unsigned originCount = 0;  // A leaf cannot have children
        std::size_t mDimension = 0;

        ////// Members for this class

        // A pointer to the representation it holds. Is shared since after a settings conversion,
        // both the converted and the original version point to the same representations
        std::shared_ptr<Representation> rep;

        // A flag that tells us if removeRedundancy() has been used on the representation
        mutable bool isNotRedundant = false;

    public:
        ////// Constructors & Destructors

        Leaf() = delete;

        Leaf(Representation &r)
                : mDimension(r.dimension()), rep(std::make_shared<Representation>(r)) {}

        Leaf(const std::shared_ptr<Representation> &ptr)
                : mDimension(ptr->dimension()), rep(ptr) {}

        Leaf(const LeafData &d) {
            assert(Representation::type() == d.typeOfRep);
            assert(d.addressToRep != 0);
            rep = std::make_shared<Representation>(*(reinterpret_cast<Representation *>( d.addressToRep )));
            assert(rep != nullptr);
            mDimension = rep->dimension();
            isNotRedundant = d.isNotRedundant;
        }

        ~Leaf() {}

        ////// Getters & Setters

        SFNEW_TYPE getType() const override { return type; }

        unsigned getOriginCount() const override { return originCount; }

        std::size_t getDimension() const override { return mDimension; }

        Representation *getRepresentation() const { return rep.get(); }

        bool isRedundant() const { return !isNotRedundant; }

        RGNData *getData() const override { return nullptr; }

        LeafData getLeafData() const override {
            return LeafData(reinterpret_cast<uintptr_t>( rep.get()), rep->type(), isNotRedundant);
        }

        void setDimension(const std::size_t d) override { mDimension = d; }

        ////// Displaying

        void print(std::ostream &ostr) const override {
            ostr << "RootGrowNode address: " << this << " own type: " << this->getType();
            if (rep != nullptr) {
                ostr << " Leaf representation type: " << rep->type() << " Leaf representation: \n"
                     << *rep << std::endl;
            } else {
                ostr << " Leaf has no representation." << std::endl;
            }
        }

        ////// RootGrowNode Interface

        // Leaves usually do not transform
        matrix_t<Number> transform(const matrix_t<Number> &) const override {
            assert(false && "Leaf::transform should never be called\n");
            return matrix_t<Number>::Zero(1, 1);
        }

        // Evaluate leaf via multiEvaluate function of the representation
        std::vector<EvaluationResult<Number>> compute(const matrix_t<Number> &param, bool useExact) const override {
            assert(rep != nullptr);

            // Optimization: Remove redundancy only when rep is being evaluated the first time
            if (!isNotRedundant) {
                rep->removeRedundancy();
                isNotRedundant = true;
            }

            // If no optimizations could be used
            COUNT("Multi constraint evaluate.");
            return rep->multiEvaluate(param, useExact);
        }

        // Leaves do not aggregate
        std::vector<EvaluationResult<Number>>
        aggregate(std::vector<std::vector<EvaluationResult<Number>>> &, const matrix_t<Number> &) const override {
            assert(false && "Leaf::aggregate should never be called\n");
            return std::vector<EvaluationResult<Number>>();
        }

        // Leaves call empty function of the representation
        bool empty() const override {
            if (RootGrowNode<Number, Converter, Setting>::mEmptyState == SETSTATE::UNKNOWN) {
                RootGrowNode<Number, Converter, Setting>::mEmptyState = rep->empty() ? SETSTATE::EMPTY
                                                                                     : SETSTATE::NONEMPTY;
            }
            return (RootGrowNode<Number, Converter, Setting>::mEmptyState == SETSTATE::EMPTY);
        }

        // Compute the point that is the supremum of the representation
        Point<Number> supremumPoint() const override {
            Point<Number> max = Point<Number>::Zero(rep->dimension());
            for (auto &point: rep->vertices()) {
                max = Point<Number>::inftyNorm(max) > Point<Number>::inftyNorm(point) ? max : point;
            }
            return max;
        }

        // Calls contains function of given representation
        bool contains(const vector_t<Number> &point) const override {
            return rep->contains(Point<Number>(point));
        }
    };

}  // namespace hypro
