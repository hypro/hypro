#include "ClassHandle.h"
#include "ObjectHandle.h"
#include "../../representations/GeometricObject.h"
#include <iostream>
#include "mex.h"
#include "matrix.h"


/**
 * The entry point to the HyPro Box class for Matalb
*@param nlhs Number of items in plhs 
*@param plhs Array of mxArray pointers to the output variables
*@param nrhs Number of items in prhs
*@param prhs Array of mxArray pointers to the input variables
*/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    // Get the command string
    char cmd[64];
	if (nrhs < 1 || mxGetString(prhs[0], cmd, sizeof(cmd)))
		mexErrMsgTxt("First input should be a command string less than 64 characters long.");
    
    /***************************************************************************
	 * Constructors
	 **************************************************************************/

    // Create new empty Box
    if (!strcmp("new", cmd) && nrhs == 1){
        if(nlhs != 1){
            mexErrMsgTxt("New: One output expected.");
        }       
        // Return a handle to a new C++ instance of HyPro Box
        plhs[0] = convertPtr2Mat<hypro::Box<double>>(new hypro::Box<double>);
        return;
    }
    
    // Check if there is a second input, which should be the class instance handle
    if (nrhs < 2)
		mexErrMsgTxt("Second input should be a Box instance handle.");
    
    // Copy
    // if(!strcmp("copy", cmd)){
    //     if(nlhs != 1){
    //         mexErrMsgTxt("Copy: One output expected.");
    //     }
    //     hypro::Box<double> *origin = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    //     plhs[0] = convertPtr2Mat<hypro::Box<double>>(new hypro::Box<double>(origin));
    // }

    // Create box from an interval
    if(!strcmp("new", cmd)){
        if(nlhs != 1){
            mexErrMsgTxt("New: One output expected.");
        }
        mxArray *m_interval_list = mxDuplicateArray(prhs[1]);
        const mwSize *dims;
        dims = mxGetDimensions(prhs[1]);
        int numdims = mxGetNumberOfDimensions(prhs[0]);
        assert(numdims==2);
        int dimy = (int)dims[0];
        int dimx = (int)dims[1];
        assert(dimx==2);
        const double *interval_list = mxGetPr(m_interval_list);
        ObjectHandle objHandle;
        std::vector<carl::Interval<double>> interval = objHandle.mInterval2HyProInterval(interval_list, dimy);
        hypro::Box<double>* box = new hypro::Box<double>(interval);
        plhs[0] = convertPtr2Mat<hypro::Box<double>>(box);
    }

    // Delete
    if (!strcmp("delete", cmd)) {
        // Destroy the Box object
        destroyObject<hypro::Box<double>>(prhs[1]);
        // Warn if other commands were ignored
        if (nlhs != 0 || nrhs != 2)
            mexWarnMsgTxt("Delete: Unexpected arguments ignored.");
        return;
    }
    
    // Get the Box instance pointer from the second input
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    
    // Call the various Box methods

    /***************************************************************************
	 * Getters & setters
	 **************************************************************************/   
    if (!strcmp("getSettings", cmd)){
        // Check parameters
        if (nlhs < 0 || nrhs < 2)
            mexErrMsgTxt("Test: Unexpected arguments.");
        // Call the method
        box->getSettings();
        return;
    }
    if(!strcmp("intervals", cmd)){
         if (nlhs < 0 || nrhs < 2)
            mexErrMsgTxt("Test: Unexpected arguments.");
        // Call the method
        std::vector<carl::Interval<double>> intervals = box->intervals();
        plhs[0] = hyProInterval2mInterval(intervals);
        return;
    }
    
    // Got here, so command not recognized
    mexErrMsgTxt("Command not recognized.");
}


