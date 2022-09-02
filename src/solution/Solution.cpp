#include "Solution.hpp"

#include <algorithm>
#include <cstdint>
#include <set>

#include "utils/FunctionTracer.hpp"

void Solution::compute([[maybe_unused]]std::vector<PackedImage> &images)
{
  FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
}

void Solution::compute(std::vector<StrideImage> &images)
{
  FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");

  using PixelIterator = std::vector<uint8_t>::iterator;

  for (auto & img : images)
  {
    std::set<PixelIterator> checkedRedPixels;

    PixelIterator redPixel = img.redPixels.begin();
    const PixelIterator end = img.redPixels.end();

    auto next = [&]()
    {
      redPixel = std::find_if(redPixel, end,
        [](uint8_t redValue) { return redValue >= 200; });

      return redPixel;
    };

    while (next() != end)
    {
      std::cout << (int) *redPixel << ' ';

      redPixel++;
    }

    std::cout << '\n';
  }
}
