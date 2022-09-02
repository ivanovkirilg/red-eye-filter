#include "Solution.hpp"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <set>

#include "utils/EyePatterns.hpp"
#include "utils/FunctionTracer.hpp"

namespace {

bool isPrettyRed(uint8_t pixelRedValue) {
  return pixelRedValue >= 200;
}

} // Anonymous namespace

void Solution::compute(std::vector<StrideImage> &images) {
  FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");

  using PixelIterator = std::vector<uint8_t>::iterator;

  for (auto & img : images) {
    PixelIterator redPixel = img.redPixels.begin();
    const PixelIterator end = img.redPixels.end();

    auto next = [end](PixelIterator& redPixel) {
      redPixel = std::find_if(redPixel + 1, end, isPrettyRed);
      return redPixel;
    };

    while (next(redPixel) != end) {
      // Look for pattern
      for (auto pattern = EYE_PATTERNS.rbegin(); pattern < EYE_PATTERNS.rend(); pattern++) {
        bool match = true;

        for (int32_t row = 0; match && (row < EYE_PATTERN_COL_SIZE); row++) {
          for (int32_t col = 0; match && (col < EYE_PATTERN_COL_SIZE); col++) {
            if (!isspace((*pattern)[row][col]) &&
                !isPrettyRed(redPixel[(img.resolution.width * row) + col])) {
              match = false;
            }
          }
        }

        if (match) {
          for (int32_t row = 0; match && (row < EYE_PATTERN_COL_SIZE); row++) {
            for (int32_t col = 0; match && (col < EYE_PATTERN_COL_SIZE); col++) {
              if (!isspace((*pattern)[row][col])) {
                redPixel[(img.resolution.width * row) + col] -= 150;
              }
            }
          }
        }
      }
    }
  }
}
