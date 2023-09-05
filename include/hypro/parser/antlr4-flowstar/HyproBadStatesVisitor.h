/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * HyproBadStatesVisitor.h
 *
 * A visitor that builds the local and global bad states and returns it to the HyproHAVisitor.h.
 *
 * @author Phillip Tse
 * @date 14.9.2017
 */

#pragma once

#include "HybridAutomatonBaseVisitor.h"
#include "../../datastructures/HybridAutomaton/Location.h"    //For locPtrComp
#include "../../datastructures/HybridAutomaton/Condition.h" //For Condition class

namespace hypro {

    template<typename Number>
    class HyproHAVisitor;

    template<typename Number>
    class HyproBadStatesVisitor : public HybridAutomatonBaseVisitor {

        friend class HyproHAVisitor<Number>;

    private:

        //Vector of declared state variables
        std::vector<std::string> &vars;

        //Set of parsed locations
        std::set<Location<Number> *> &locSet;

        //Auxiliary variable since this visitor returns local and global badstates
        std::vector<Condition<Number>> gBadStates;

        //Constructor
        HyproBadStatesVisitor(std::vector<std::string> &varVec, std::set<Location<Number> *> &lSet);

        ~HyproBadStatesVisitor();

    public:

        //Getter for global badstates
        std::vector<Condition<Number>> getGlobalBadStates() { return gBadStates; }

        //Inherited from HybridAutomatonBaseVisitor
        antlrcpp::Any visitUnsafeset(HybridAutomatonParser::UnsafesetContext *ctx) override;

        antlrcpp::Any visitLbadstate(HybridAutomatonParser::LbadstateContext *ctx) override;

        antlrcpp::Any visitGbadstate(HybridAutomatonParser::GbadstateContext *ctx) override;

    };

} //namespace hypro

#include "HyproBadStatesVisitor.tpp"
