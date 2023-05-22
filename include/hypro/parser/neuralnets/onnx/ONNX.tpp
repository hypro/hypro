#include "fstream"
#include "ONNX.h"

namespace hypro {

template <typename Number>
ONNX<Number>::ONNX(const std::string file_name){
  // Open file and move current position in file to the end
  std::ifstream input(file_name, std::ios::ate | std::ios::binary);

  assert(input.fail() && "hypro.parser.neuralnets.onnx: Could not open the input file!");

  // Get current position in file
  auto size = input.tellg();

  // Move to start of file
  input.seekg(0, std::ios::beg);

  // Read raw binary data
  std::vector<char> buffer(size);
  input.read(buffer.data(), size);

  // Parse protobuf model
  onnx::ModelProto model;
  model.ParseFromArray(buffer.data(), size);

  this->internal_model_ = model;
}

template <typename Number>
onnx::ModelProto ONNX<Number>::getModel() const {
  return this->internal_model_;
}

}