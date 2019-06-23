#include "mex.hpp"
#include "mexAdapter.hpp"

#include "representations/@MHyProBox/MBoxAdvanced.h"

using namespace matlab::data;
using matlab::mex::ArgumentList;

class MexFunction : public matlab::mex::Function {
public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
    if (!inputs.empty()) {
        // MEX function called with no input arguments
        MBox::process(inputs);
    }
};