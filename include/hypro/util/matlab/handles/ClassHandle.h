/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* This is the class handler for mhypro. It is needed for comunication between
 * Matalb and HyPro.
 */

#ifndef CLASS_HANDLE_H
#define CLASS_HANDLE_H

#include <cstring>
#include <mex.h>
#include <stdint.h>
#include <string>
#include <typeinfo>

#define CLASS_HANDLE_SIGNATURE 0xFF00F0A5

template<class T>
class ClassHandle {
public:
    ClassHandle(T *ptr)
            : signature_m(CLASS_HANDLE_SIGNATURE), name_m(typeid(T).name()), ptr_m(ptr) {}

    ~ClassHandle() {
        signature_m = 0;
        delete ptr_m;
    }

    bool isValid() { return ((signature_m == CLASS_HANDLE_SIGNATURE) && !strcmp(name_m.c_str(), typeid(T).name())); }

    T *ptr() { return ptr_m; }

private:
    uint32_t signature_m;
    const std::string name_m;
    T *const ptr_m;
};

template<class T>
inline mxArray *convertPtr2Mat(T *ptr) {
    mexLock();
    mxArray *out = mxCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
    *((uint64_t *) mxGetData(out)) = reinterpret_cast<uint64_t>( new ClassHandle<T>(ptr));
    // mexPrintf("convertPtr2Mat %p\n", out);
    return out;
}

template<class T>
inline mxArray *convertSmartPtr2Mat(T *ptr) {
    mxArray *out = mxCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
    *((uint64_t *) mxGetData(out)) = reinterpret_cast<uint64_t>( new ClassHandle<T>(ptr));
    // mexPrintf("convertPtr2Mat %p\n", out);
    return out;
}

template<class T>
inline ClassHandle<T> *convertMat2HandlePtr(const mxArray *in) {
    if (mxGetNumberOfElements(in) != 1 || mxGetClassID(in) != mxUINT64_CLASS || mxIsComplex(in))
        mexErrMsgTxt("Input must be a real uint64 scalar.");
    ClassHandle<T> *ptr = reinterpret_cast<ClassHandle<T> *>( *((uint64_t *) mxGetData(in)));
    if (!ptr->isValid())
        mexErrMsgTxt("Handle not valid.");
    // mexPrintf("convertMat2HandlePtr %p\n", ptr);
    return ptr;
}

template<class T>
inline T *convertMat2Ptr(const mxArray *in) {
    T *temp = convertMat2HandlePtr<T>(in)->ptr();
    // mexPrintf("convertMat2Ptr %p\n", temp);
    return temp;
}

template<class T>
inline void destroyObject(const mxArray *in) {
    delete convertMat2HandlePtr<T>(in);
    mexUnlock();
}

template<class T>
inline void destroySmartObject(const mxArray *in) {
    delete convertMat2HandlePtr<T>(in);
}

#endif
