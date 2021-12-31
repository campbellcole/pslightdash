//
// Created by Campbell Cole on 12/30/21.
//

#include <cmath>

#include "util/math.h"

#define PI 3.1415927f

namespace dash::util::math {

  void takeEvens(const float *from, float *to, size_t fromSize, WINDOW_FUNCTION window) {
    for (size_t i = 0, t = 0; i < fromSize; i+=2, t++) {
      to[t] = from[i] * (window != nullptr ? (*window)(i, fromSize) : 1.0f);
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