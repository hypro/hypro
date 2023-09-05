#include <fstream>
#include <cassert>

#include "hypro/parser/neuralnets/onnx/onnx.proto3.pb.h"

void print_dim(const ::onnx::TensorShapeProto_Dimension &dim)
{
  switch (dim.value_case())
  {
  case onnx::TensorShapeProto_Dimension::ValueCase::kDimParam:
    std::cout << dim.dim_param();
    break;
  case onnx::TensorShapeProto_Dimension::ValueCase::kDimValue:
    std::cout << dim.dim_value();
    break;
  default:
    assert(false && "should never happen");
  }
}

void print_io_info(const ::google::protobuf::RepeatedPtrField<::onnx::ValueInfoProto> &info)
{
  for (auto input_data : info)
  {
    auto shape = input_data.type().tensor_type().shape();
    std::cout << "  " << input_data.name() << ":";
    std::cout << "[";
    if (shape.dim_size() != 0)
    {
      int size = shape.dim_size();
      for (int i = 0; i < size - 1; ++i)
      {
        print_dim(shape.dim(i));
        std::cout << ", ";
      }
      print_dim(shape.dim(size - 1));
    }
    std::cout << "]\n";
  }
}

int main(int argc, char **argv)
{
  std::ifstream input("/home/$USER/repositories/hypro/examples/onnx/ACASXU_run2a_1_1_batch_2000.onnx", std::ios::ate | std::ios::binary); // open file and move current position in file to the end

  std::streamsize size = input.tellg(); // get current position in file
  input.seekg(0, std::ios::beg);        // move to start of file

  std::vector<char> buffer(size);
  input.read(buffer.data(), size); // read raw data

  onnx::ModelProto model;
  model.ParseFromArray(buffer.data(), size); // parse protobuf

  auto graph = model.graph();

  std::cout << "graph inputs:\n";
  print_io_info(graph.input());

  std::cout << "graph outputs:\n";
  print_io_info(graph.output());
  return 0;
}
