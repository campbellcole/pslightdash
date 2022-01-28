//
// Created by Campbell Cole on 12/30/21.
//

#include <cmath>

#include "util/math.h"

#define PI 3.1415927f

namespace dash::util::math {

  void takeEvens(const float *from, float *to, size_t fromSize, unsigned int step, WINDOW_FUNCTION window) {
    for (size_t i = 0, t = 0; i < fromSize; i+=step, t++) {
      to[t] = from[i] * (window != nullptr ? (*window)(i, fromSize) : 1.0f);
    }
  }

  void combArray(const float *from, float *to, size_t fromSize, WINDOW_FUNCTION window, int windowMode) {
    size_t N = windowMode ? fromSize / 2 : fromSize;
    for (size_t i = 0, l = 0, r = fromSize/2; i < fromSize; i+=2, l++, r++) {
      to[l] = from[i] * (window != nullptr ? (*window)(windowMode ? l : i, N) : 1.0f);
      to[r] = from[i+1] * (window != nullptr ? (*window)(windowMode ? l : (i+1), N) : 1.0f);
      // if windowMode is 1, we want to use l because 0 <= l < fromSize / 2
      // if windowMode is 0, we want to use i because 0 <= i < fromSize
      // N will be either fromSize / 2 or fromSize accordingly
    }
  }

  float windowHann(unsigned int n, unsigned int N) {
    return powf(
      sinf((PI * static_cast<float>(n)) / static_cast<float>(N)), 2
    );
  }

  void calculateMagnitudesLog(float *magnitudes, const float *re, const float *im, size_t len) {
    for (size_t i = 0; i < len; i++) {
      magnitudes[i] = 10 * log10((re[i] * re[i]) + (im[i] * im[i]) + 1);
    }
  }

  void calculateMagnitudes(float *magnitudes, const float *re, const float *im, size_t len) {
    for (size_t i = 0; i < len; i++) {
      magnitudes[i] = sqrt((re[i] * re[i]) + (im[i] * im[i]));
    }
  }

}