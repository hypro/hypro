#include "MHyProConstraintSet.h"

/**
 * @brief Creates an empty constraint set
 **/
void MHyProConstraintSet::new_empty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProConstraintSet - new_empty: One output expected.");
    if(nrhs > 2)
        mexWarnMsgTxt("MHyProConstraintSet - new_empty: One or more input arguments were ignored.");

    plhs[0] = convertPtr2Mat<hypro::ConstraintSet<double>>(new hypro::ConstraintSet<double>);
}

/**
 * @brief
 **/
void MHyProConstraintSet::isAxisAligned(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProConstraintSet - isAxisAligned: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProConstraintSet - isAxisAligned: One argument missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProConstraintSet - isAxisAligned: One or more input arguments were ignored.");

    hypro::ConstraintSet<double>* temp = convertMat2Ptr<hypro::ConstraintSet<double>>(prhs[2]);
    const bool empty = temp->isAxisAligned();
    plhs[0] = mxCreateLogicalScalar(empty);
}

/**
 * @brief
 **/
void MHyProConstraintSet::addConstraint(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("MHyProConstraintSet - addConstraint: One or more arguments are missing!");
    if(nrhs > 5)
        mexWarnMsgTxt("MHyProConstraintSet - addConstraint: One or more input arguments were ignored.");


    const mwSize *dims;
    int dimx, dimy;

    hypro::ConstraintSet<double>* temp = convertMat2Ptr<hypro::ConstraintSet<double>>(prhs[2]);
    const double offset = (const double) mxGetScalar(prhs[4]);
    dims = mxGetDimensions(prhs[3]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];

    const hypro::vector_t<double> hy_vec = ObjectHandle::mVector2Hypro(prhs[3], dimy);
    temp->addConstraint(hy_vec, offset);
}

/**
 * @brief
 **/
void MHyProConstraintSet::type(int nlhs, mxArray* plhs[], int rhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProConstraintSet - type: Expecting one output value!");
    std::string ans = "MHyProConstraintSet";
    plhs[0] = mxCreateString(ans.c_str());
}

/**
 * @brief
 **/
void MHyProConstraintSet::reduceNumberRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("HyProConstraintSet - reduceNumberRepresentation: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("HyProConstraintSet - reduceNumberRepresentation: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProConstraintSet - reduceNumberRepresentation: One or more input arguments were ignored.");


    hypro::ConstraintSet<double>* temp = convertMat2Ptr<hypro::ConstraintSet<double>>(prhs[2]);
    const unsigned u = (const unsigned) mxGetScalar(prhs[3]);
    hypro::ConstraintSet<double> obj = temp->reduceNumberRepresentation(u);
    hypro::ConstraintSet<double>* b = new hypro::ConstraintSet<double>(obj);
    plhs[0] = convertPtr2Mat<hypro::ConstraintSet<double>>(b);
}

// /**
//  * @brief
//  **/
// template<typename From, typename To, typename S>
// void MHyProConstraintSet::convert(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MHyProConstraintSet - convert: One output is expected.");
//     if(nrhs < 6)
//         mexErrMsgTxt("MHyProConstraintSet - convert: One or more arguments are missing.");
    
//     char from[64];
//     char to[64];
//     char s[64];
//     mxGetString(prhs[3], from, sizeof(from));
//     mxGetString(prhs[4], to, sizeof(to));
//     mxGetString(prhs[5], s, sizeof(s));

//     hypro::ConstraintSet<double> 

//     hypro::ConstraintSet<to,s> con = 

// }


/**
* @brief The entry point to the HyPro Constraint Set class for Matalb.
* @param nlhs Number of items in plhs 
* @param plhs Array of mxArray pointers to the output variables
* @param nrhs Number of items in prhs
* @param prhs Array of mxArray pointers to the input variables
**/
void MHyProConstraintSet::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MHyProConstraintSet - First input should be a command string less than 64 characters long.");

    if(!strcmp("new_empty", cmd)){
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("new_mat_vec", cmd)){  
        new_mat_vec(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("copy", cmd)){
        copyObj(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("delete", cmd)) {
        deleteObject(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("matrix", cmd)){
        matrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("vector", cmd)){
        vector(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("isAxisAligned", cmd)){
        isAxisAligned(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("addConstraint", cmd)){
        addConstraint(nlhs, plhs, nrhs, prhs);
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
        intersectHalfspaces(nlhs, plhs, nrhs, prhs);
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
    if(!strcmp("clear", cmd)){
        clear(nlhs, plhs, nrhs, prhs);
        return;
    }
    mexErrMsgTxt("MHyProConstraintSet - Command not recognized.");
}