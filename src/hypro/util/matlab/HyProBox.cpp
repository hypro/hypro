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
        // if(nlhs != 2){
        //     mexErrMsgTxt("New: One output expected.");
        // }
        mxArray *m_in_intervals;
        const mwSize *dims;
        double *in;
        int dimx, dimy, numdims;

        m_in_intervals = mxDuplicateArray(prhs[1]);

        dims = mxGetDimensions(prhs[1]);
        numdims = mxGetNumberOfDimensions(prhs[1]);
        dimy = (int) dims[0];
        dimx = (int) dims[1];

        // Ensure that the user entered a list of intervals
        if(dimx != 2){
            mexErrMsgTxt("You have to enter a nx2-matrix! (e.g.:[lower_1 upper_1; lower_2 upper_2])");
        }
        in = mxGetPr(m_in_intervals);
        

        ObjectHandle objHandle;
        std::vector<carl::Interval<double>> intervals = objHandle.mInterval2HyProInterval(m_in_intervals, dimx, dimy);
        hypro::Box<double>* box = new hypro::Box<double>(intervals);
        plhs[0] = convertPtr2Mat<hypro::Box<double>>(box);
        return;
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
    
    // // Call the various Box methods

    // /***************************************************************************
	//  * Getters & setters
	//  **************************************************************************/   
    // ObjectHandle obj_handle;
    // if (!strcmp("getSettings", cmd)){
    //     // Check parameters
    //     if (nlhs < 0 || nrhs < 2)
    //         mexErrMsgTxt("Test: Unexpected arguments.");
    //     // Call the method
    //     box->getSettings();
    //     return;
    // }
    if(!strcmp("intervals", cmd)){
        if (nlhs < 0 || nrhs < 2){
            mexErrMsgTxt("Test: Unexpected arguments.");
        }   
        mxArray* m_out_intervals;
        double* out;
        ObjectHandle obj_handle;
        int dimy, dimx;

        std::vector<carl::Interval<double>> intervals = box->intervals();

        dimy = intervals.size();
        dimx = 2;
        m_out_intervals = plhs[0] = mxCreateDoubleMatrix(dimy, dimx, mxREAL);
        out = mxGetPr(m_out_intervals);

        obj_handle.hyProInterval2mInterval(intervals, out, dimx, dimy);
        return;
    }
    
    // Got here, so command not recognized
    mexErrMsgTxt("Command not recognized");
}


