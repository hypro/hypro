// #include "HyProTaylorModel.h"

// /**
//  * @brief
//  **/
// void HyProTaylorModel::emptyTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("HyProTaylorModel - emptyTM: One output is expected.");
//     plhs[0] = convertPtr2Mat<hypro::TaylorModel<double>>(new hypro::TaylorModel<double>);
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::polyn_interTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("HyProTaylorModel - polyn_interTM: One output is expected.");
//     if(nrhs < 3)
//         mexErrMsgTxt("HyProTaylorModel - polyn_interTM: One or more arguments are missing.");

//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::polynTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::interTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("HyProTaylorModel - interTM: One output is expected.");
//     if(nrhs < 3)
//         mexErrMsgTxt("HyProTaylorModel - interTM: One or more arguments are missing.");
    
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
// void HyProTaylorModel::initlistTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::initlist_interTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::termTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::varTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::deleteTM(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     destroyObject<hypro::TaylorModel<double>>(prhs[2]);
//     // Warn if other commands were ignored
//     if (nlhs != 0 || nrhs != 3)
//         mexWarnMsgTxt("HyProTaylorModel - delete: Unexpected arguments ignored.");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::isZero(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("HyProTaylorModel - isZero: Expecting an output!");
//     if(nrhs < 3)
//         mexErrMsgTxt("HyProTaylorModel - isZero: One argument missing!");

//     hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     const bool ans = tm->isZero();
//     plhs[0] = mxCreateLogicalScalar(ans);
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::isConstant(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("HyProTaylorModel - isConstant: Expecting an output!");
//     if(nrhs < 3)
//         mexErrMsgTxt("HyProTaylorModel - isConstant: One argument missing!");

//     hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     const bool ans = tm->isConstant();
//     plhs[0] = mxCreateLogicalScalar(ans);
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::isLinear(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("HyProTaylorModel - isLinear: Expecting an output!");
//     if(nrhs < 3)
//         mexErrMsgTxt("HyProTaylorModel - isLinear: One argument missing!");

//     hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     const bool ans = tm->isLinear();
//     plhs[0] = mxCreateLogicalScalar(ans);
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::rmConstantTerm(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("HyProTaylorModel - rmConstantTerm: Expecting an output!");
//     if(nrhs < 3)
//         mexErrMsgTxt("HyProTaylorModel - rmConstantTerm: One argument missing!");
    
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
// void HyProTaylorModel::tmOrder(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("HyProTaylorModel - tmOrder: Expecting an output!");
//     if(nrhs < 3)
//         mexErrMsgTxt("HyProTaylorModel - tmOrder: One argument missing!");
    
//     mxArray *m_out;
//     double *out;

//     hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     exponent order = tm->tmOrder();

//     m_out = plhs[0] = mxCreateDoubleScalar(order);

// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::pow(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::checkConsistency(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nrhs < 3)
//         mexErrMsgTxt("HyProTaylorModel - tmOrder: One argument missing!");

//     hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     tm->checkConsistency();
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::has(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("HyProTaylorModel - has: Expecting an output!");
//     if(nrhs < 4)
//         mexErrMsgTxt("HyProTaylorModel - has: One argument missing!");

//     mexErrMsgTxt("not implemented");
//     // hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     // const bool ans = tm->has();
//     // plhs[0] = mxCreateLogicalScalar(ans);
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::cutoff(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::cutoff_nr(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::truncation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::truncation_nr(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::enclosure(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::enclosure_nr(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::poly_enclosure(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::normalize(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::add(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("HyProTaylorModel - add: Expecting an output!");
//     if(nrhs < 4)
//         mexErrMsgTxt("HyProTaylorModel - add: One argument missing!");

//     const hypro::TaylorModel<double>* tm = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[2]);
//     const hypro::TaylorModel<double>* tm_2 = convertMat2Ptr<hypro::TaylorModel<double>>(prhs[3]);
//    // hypro::TaylorModel<double> sum = tm->operator+(*tm_2);
//    mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::subtract(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::mult_inter(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::mult_tm(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::mult_term(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
//  * @brief
//  **/
// void HyProTaylorModel::mult_var(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     mexErrMsgTxt("not implemented");
// }

// /**
// * @brief The entry point to the HyPro TaylorModel class for Matalb.
// * @param nlhs Number of items in plhs 
// * @param plhs Array of mxArray pointers to the output variables
// * @param nrhs Number of items in prhs
// * @param prhs Array of mxArray pointers to the input variables
// **/
// void HyProTaylorModel::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     // Get the command string
//     char cmd[64];
//     if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
//         mexErrMsgTxt("HyProTaylorModel - First input should be a command string less than 64 characters long.");
    
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

//     mexErrMsgTxt("HyProTaylorModel - Command not recognized.");
// }
