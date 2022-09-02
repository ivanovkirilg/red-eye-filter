#ifndef RED_EYE_SOLUTION
#define RED_EYE_SOLUTION

#include <cstdint>

#include "utils/Image.hpp"
#include "utils/FunctionTracer.hpp"

class Solution {
public:
  void compute([[maybe_unused]]std::vector<PackedImage> &images) {
    FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
    //TODO: fill solution
  }

  void compute([[maybe_unused]]std::vector<StrideImage> &images) {
    FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
    //TODO: fill solution
  }
};

#endif // RED_EYE_SOLUTION
