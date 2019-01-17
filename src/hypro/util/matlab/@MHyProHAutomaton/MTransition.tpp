// /**
//  * @brief
//  **/
// template<typename T>
// void MAutomatonComponents<T>::getDotRepresentation(int nlhs, mxArray* plrhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MAutomatonComponents - getDotRepresentation: Expecting an output!");
//     if(nrhs < 4)
//         mexErrMsgTxt("MAutomatonComponents - getDotRepresentation: One or more arguments are missing!");

//     T* obj = convertMat2Ptr<T>(plhs[2]);
//     std::vector<std::string> vec(nrhs - 3);

//     for(int i = 2; i < (nrhs - 3); i++){
//         std::string str = mxArrayToString(prhs[i]);
//         vec.emplace_back(str);
//     }
    
// }