#ifndef HYPRO_ONNX_H
#define HYPRO_ONNX_H

#include "onnx.proto3.pb.h"

namespace hypro {

template <typename Number>
class ONNX {
  private:
      onnx::ModelProto internal_model_;

  public:
      /**
       * @brief Build an ONNX model from the given input file.
       *
       * @param[in] filename Input file name.
       */
      ONNX(const std::string file_name);

      /**
       * @brief Get the internal ONNX model.
       *
       * @return ONNX model.
       */
      onnx::ModelProto getModel() const;


};

} // hypro

#include "ONNX.tpp"

#endif //HYPRO_ONNX_H