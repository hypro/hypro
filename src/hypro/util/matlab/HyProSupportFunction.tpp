#include "HyProSupportFunction.h"

/**
 * @brief
 **/
void HyProSupportFunction::cleanUp(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    mexErrMsgTxt("not implemented");
}

/**
 * @brief
 **/
void HyProSupportFunction::unequal(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @brief
 **/
void HyProSupportFunction::reduceNumberRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @brief
 **/
void HyProSupportFunction::type(int nlhs, mxArray* plhs[], int rhs, const mxArray* prhs[]){

}

/**
 * @brief
 **/
void HyProSupportFunction::ostream(int nlhs, mxArray* plhs[], int rhs, const mxArray* prhs[]){

}

/**
* @brief The entry point to the HyPro Support Function class for Matalb.
* @param nlhs Number of items in plhs 
* @param plhs Array of mxArray pointers to the output variables
* @param nrhs Number of items in prhs
* @param prhs Array of mxArray pointers to the input variables
**/
void HyProSupportFunction::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("HyProConstraintSet - First input should be a command string less than 64 characters long.");
    
    /***************************************************************************
     * Constructors
     **************************************************************************/

    if (!strcmp("new_matrix", cmd) && nrhs == 2){  
        new_matrix(nlhs, plhs, nrhs ,prhs);
        return;
    }

    if (!strcmp("new_mat_vec", cmd) && nrhs == 2){  
        new_mat_vec(nlhs, plhs, nrhs, prhs);
        return;
    }
    


    // Check if there is a second input, which should be the class instance handle
    if (nrhs < 2){
        mexErrMsgTxt("Second input should be a Box instance handle.");
    }
    
    if(!strcmp("copy", cmd)){
        copyObj(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("delete", cmd)) {
        deleteObject(nlhs, plhs, nrhs, prhs);
        return;
    }
    
    /***************************************************************************
     * Getters & setters
     **************************************************************************/ 

    if(!strcmp("matrix", cmd)){
        matrix(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("vector", cmd)){
        vector(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("isEmpty", cmd)){
        is_empty(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("vertices", cmd)){
        vertices(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("==", cmd)){
        equal(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("!=", cmd)){
        unequal(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("<<", cmd)){
        ostream(nlhs, plhs, nrhs, prhs);
        return;
    }

    /**************************************************************************
     * General interface
    **************************************************************************/
    
    if(!strcmp("dimension", cmd)){
        dimension(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("removeRedundancy", cmd)){
        removeRedundancy(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("size", cmd)){
        size(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("type", cmd)){
        type(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("reduceNumberRepresentation", cmd)){
        reduceNumberRepresentation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("satisfiesHalfspace", cmd)){
        satisfiesHalfspace(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("satisfiesHalfspaces", cmd)){
        satisfiesHalfspaces(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("project", cmd)){
        project(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("linearTransformation", cmd)){
        linearTransformation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("affineTransformation", cmd)){
        affineTransformation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("minkowskiSum", cmd)){
        minkowskiSum(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("intersect", cmd)){
        intersect(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("intersectHalfspace", cmd)){
        intersectHalfspace(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("intersectHalfspaces", cmd)){
        reduceNumberRepresentation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("contains_point", cmd)){
        contains_point(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("contains_set", cmd)){
        contains_object(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("unite", cmd)){
        unite_single(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("unite_objects", cmd)){
        unite_vec(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("reduceRepresentation", cmd)){
        reduceRepresentation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("cleanUp", cmd)){
        cleanUp(nlhs, plhs, nrhs, prhs);
        return;
    }

    mexErrMsgTxt("HyProHyProConstraintSet - Command not recognized.");
}