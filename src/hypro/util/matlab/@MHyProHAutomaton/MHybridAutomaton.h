#pragma once

#include "mex.h"
#include "matrix.h"
#include "../Handles/ClassHandle.h"
#include "../Handles/ObjectHandle.h"

class MHybridAutomaton{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void new_empty(int, mxArray**, int, const mxArray**);
        static void copy(int, mxArray**, int, const mxArray**);
        // static void new_loc_init(int, mxArray**, int, const mxArray**);
        static void delete_autom(int, mxArray**, int, const mxArray**);
        static void getLocations(int, mxArray**, int, const mxArray**);
        static void getLocation_by_hash(int, mxArray**, int, const mxArray**);
        static void getLocation_by_name(int, mxArray**, int, const mxArray**);
        static void getTransitions(int, mxArray**, int, const mxArray**);
        static void getInitialStates(int, mxArray**, int, const mxArray**);
        static void getLocalBadStates(int, mxArray**, int, const mxArray**);
        static void getGlobalBadStates(int, mxArray**, int, const mxArray**);
        static void dimension(int, mxArray**, int, const mxArray**);
        static void getVariables(int, mxArray**, int, const mxArray**);
        static void getLabels(int, mxArray**, int, const mxArray**);
        static void setLocations(int, mxArray**, int, const mxArray**);
        static void setInitialStates(int, mxArray**, int, const mxArray**);
        static void setLocalBadStates(int, mxArray**, int, const mxArray**);
        static void setGlobalBadStates(int, mxArray**, int, const mxArray**);
        static void setVariables(int, mxArray**, int, const mxArray**);
        static void addLocation(int, mxArray**, int, const mxArray**);
        // static void addTransition(int, mxArray**, int, const mxArray**);
        static void addInitialState(int, mxArray**, int, const mxArray**);
        static void addLocalBadState(int, mxArray**, int, const mxArray**);
        static void addGlobalBadState(int, mxArray**, int, const mxArray**);
        // static void removeTransition(int, mxArray**, int, const mxArray**);
        static void decompose(int, mxArray**, int, const mxArray**);
        static void reduce(int, mxArray**, int, const mxArray**);
        // static void isComposedOf(int, mxArray**, int, const mxArray**);
        static void getDotRepresentation(int, mxArray**, int, const mxArray**);
        static void getStatistics(int, mxArray**, int, const mxArray**);
        static void equals(int, mxArray**, int, const mxArray**);
        static void unequals(int, mxArray**, int, const mxArray**);
        // static void or_operator(int, mxArray**, int, const mxArray**);
        static void plus(int, mxArray**, int, const mxArray**);
        static void outstream(int, mxArray**, int, const mxArray**);
        static void checkConsistency(int, mxArray**, int, const mxArray**);
};

#include "MHybridAutomaton.tpp"