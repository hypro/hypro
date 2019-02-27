// #include "MHyProTaylorModel.h"

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::emptyTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MHyProTaylorModel - emptyTM: One output is expected.");
//     plhs[0] = convertPtr2Mat<hypro::TaylorModel<double>>(new hypro::TaylorModel<double>);
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::polyn_interTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MHyProTaylorModel - polyn_interTM: One output is expected.");
//     if(nrhs < 3)
//         mexErrMsgTxt("MHyProTaylorModel - polyn_interTM: One or more arguments are missing.");

//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::polynTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::interTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MHyProTaylorModel - interTM: One output is expected.");
//     if(nrhs < 3)
//         mexErrMsgTxt("MHyProTaylorModel - interTM: One or more arguments are missing.");
    
//     mxArray *m_in_interval;
//     double* in_interval;

//     m_in_interval = mxDuplicateArray(prhs[2]);
//     in_interval = mxGetPr(m_in_interval);
//     carl::Interval<double> inter = ObjectHandle::mInterval2Hypro(in_interval);
//     hypro::TaylorModel<double>* tm = new hypro::TaylorModel<double>(inter);
//     plhs[0] = convertPtr2Mat<hypro::TaylorModel<double>>(tm);
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::initlistTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::initlist_interTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::termTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::varTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::deleteTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     destroyObject<hypro::TaylorModel<double>>(prhs[2]);
//     // Warn if other commands were ignored
//     if (nlhs != 0 || nrhs != 3)
//         mexWarnMsgTxt("MHyProTaylorModel - delete: Unexpected arguments ignored.");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::isZero(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("MHyProTaylorModel - isZero: Expecting an output!");
//     if(nrhs < 3)
//         mexErrMsgTxt("MHyProTaylorModel - isZero: One argument missing!");

//     hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     const bool ans = tm->isZero();
//     plhs[0] = mxCreateLogicalScalar(ans);
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::isConstant(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("MHyProTaylorModel - isConstant: Expecting an output!");
//     if(nrhs < 3)
//         mexErrMsgTxt("MHyProTaylorModel - isConstant: One argument missing!");

//     hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     const bool ans = tm->isConstant();
//     plhs[0] = mxCreateLogicalScalar(ans);
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::isLinear(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("MHyProTaylorModel - isLinear: Expecting an output!");
//     if(nrhs < 3)
//         mexErrMsgTxt("MHyProTaylorModel - isLinear: One argument missing!");

//     hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     const bool ans = tm->isLinear();
//     plhs[0] = mxCreateLogicalScalar(ans);
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::rmConstantTerm(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("MHyProTaylorModel - rmConstantTerm: Expecting an output!");
//     if(nrhs < 3)
//         mexErrMsgTxt("MHyProTaylorModel - rmConstantTerm: One argument missing!");
    
//     mxArray* m_out;
//     double *out;

//     hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     const carl::Interval<double> inter = tm->rmConstantTerm;
//     m_out = plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
//     out = mxGetPr(m_out);
//     ObjectHandle::convert2matlab(inter, out, 2, 1);
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::tmOrder(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("MHyProTaylorModel - tmOrder: Expecting an output!");
//     if(nrhs < 3)
//         mexErrMsgTxt("MHyProTaylorModel - tmOrder: One argument missing!");
    
//     mxArray *m_out;
//     double *out;

//     hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     exponent order = tm->tmOrder();

//     m_out = plhs[0] = mxCreateDoubleScalar(order);

// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::pow(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::checkConsistency(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nrhs < 3)
//         mexErrMsgTxt("MHyProTaylorModel - tmOrder: One argument missing!");

//     hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     tm->checkConsistency();
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::has(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("MHyProTaylorModel - has: Expecting an output!");
//     if(nrhs < 4)
//         mexErrMsgTxt("MHyProTaylorModel - has: One argument missing!");

//     mexErrMsgTxt("not implemented");
//     // hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     // const bool ans = tm->has();
//     // plhs[0] = mxCreateLogicalScalar(ans);
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::cutoff(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::cutoff_nr(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::truncation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::truncation_nr(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::enclosure(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::enclosure_nr(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::poly_enclosure(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::normalize(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::add(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("MHyProTaylorModel - add: Expecting an output!");
//     if(nrhs < 4)
//         mexErrMsgTxt("MHyProTaylorModel - add: One argument missing!");

//     const hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     const hypro::TaylorModel<double>* tm_2 = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[3]);
//    // hypro::TaylorModel<double> sum = tm->operator+(*tm_2);
//    mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::subtract(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::mult_inter(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::mult_tm(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::mult_term(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void MHyProTaylorModel::mult_var(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
// * @brief The entry point to the HyPro TaylorModel class for Matalb.
// * @param nlhs Number of items in plhs 
// * @param plhs Array of mxArray pointers to the output variables
// * @param nrhs Number of items in prhs
// * @param prhs Array of mxArray pointers to the input variables
// **/
// void MHyProTaylorModel::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     // Get the command string
//     char cmd[64];
//     if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
//         mexErrMsgTxt("MHyProTaylorModel - First input should be a command string less than 64 characters long.");
    
//     /***************************************************************************
//      * Constructors
//      **************************************************************************/

//     if (!strcmp("new_empty", cmd) && nrhs == 2){  
//         emptyTM(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("new_interval", cmd)){
//         interTM(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("new_poly_inter", cmd)){
//         polyn_interTM(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("new_list",cmd)){
//         initlistTM(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("new_list_inter",cmd)){
//         initlist_interTM(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("new_term",cmd)){
//         termTM(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("new_var",cmd)){
//         varTM(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if (!strcmp("delete", cmd)) {
//         deleteTM(nlhs, plhs, nrhs, prhs);
//         return;
//     }
    
//     /***************************************************************************
//      * Getters & setters
//      **************************************************************************/ 

//     if(!strcmp("isZero", cmd)){
//         isZero(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("isConstant", cmd)){
//         isConstant(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("isConstant", cmd)){
//         isConstant(nlhs, plhs, nrhs, prhs);
//         return;
//     }
    
//     if(!strcmp("isLinear", cmd)){
//         isLinear(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("rmConstantTerm", cmd)){
//         rmConstantTerm(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("tmOrder", cmd)){
//         tmOrder(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("pow", cmd)){
//         pow(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("checkConsistency", cmd)){
//         checkConsistency(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("has", cmd)){
//         has(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("cutoff", cmd)){
//         cutoff(nlhs, plhs, nrhs, prhs);
//         return;
//     }  

//     if(!strcmp("cutoff_nr", cmd)){
//         cutoff_nr(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("truncation", cmd)){
//         truncation(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("truncation_nr", cmd)){
//         truncation_nr(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("enclosure", cmd)){
//         enclosure(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("enclosure_nr", cmd)){
//         enclosure_nr(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("poly_enclosure", cmd)){
//         poly_enclosure(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("normalize", cmd)){
//         normalize(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("add", cmd)){
//         add(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("subtract", cmd)){
//         subtract(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("mult_inter", cmd)){
//         mult_inter(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("mult_tm", cmd)){
//         mult_tm(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("mult_term", cmd)){
//         mult_term(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("mult_var", cmd)){
//         mult_var(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     mexErrMsgTxt("MHyProTaylorModel - Command not recognized.");
// }
