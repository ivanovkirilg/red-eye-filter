#include "Solution.hpp"

#include <algorithm>
#include <cctype>
#include <functional>
#include <cstdint>

#include "utils/EyePatterns.hpp"
#include "utils/FunctionTracer.hpp"

using ColorIterator = std::vector<uint8_t>::iterator;

namespace {

bool isPrettyRed(uint8_t pixelRedValue) {
  return pixelRedValue >= 200;
}

void actOnPattern(
        const EyePattern& pattern,
        const std::function<bool(int32_t row, int32_t col)>& onPixel) {
  bool run = true;

  for (int32_t row = 0; run && (row < EYE_PATTERN_COL_SIZE); row++) {
    for (int32_t col = 0; run && (col < EYE_PATTERN_COL_SIZE); col++) {
      if (!isspace((pattern)[row][col])) {
        run = onPixel(row, col);
      }
    }
  }
}

} // Anonymous namespace

void Solution::compute(std::vector<StrideImage> &images) {
  FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");

  for (auto & img : images) {
    ColorIterator redPixel = img.redPixels.begin();
    const ColorIterator end = img.redPixels.end();

    auto next = [end](ColorIterator& redPixel) {
      return ( redPixel = std::find_if(redPixel + 1, end, isPrettyRed) );
    };

    while (next(redPixel) != end) {
      for (auto pattern = EYE_PATTERNS.rbegin();
                pattern < EYE_PATTERNS.rend();
                pattern++) {

        const size_t rowLen = img.resolution.width;
        bool match = true;

        actOnPattern(*pattern, [&](int32_t row, int32_t col) {
          match = isPrettyRed(redPixel[(rowLen * row) + col]);
          return match;
        });

        if (match) {
          actOnPattern(*pattern, [&](int32_t row, int32_t col) {
            redPixel[(rowLen * row) + col] -= 150;
            return true;
          });

          break;
        }
      }
    }
  }
}
