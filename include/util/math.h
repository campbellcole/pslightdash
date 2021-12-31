//
// Created by Campbell Cole on 12/30/21.
//

#ifndef PSLIGHTDASH_MATH_H
#define PSLIGHTDASH_MATH_H

namespace dash::util::math {

  typedef float (*WINDOW_FUNCTION)(unsigned int n, unsigned int N);

  /**
   * Takes every other element from an array.
   *
   * \Preconditions
   *  - `from` array has an even number of elements
   *  <br>
   *  - `to` array has a capacity of at least `fromSize / 2`
   * @param from The array to take from
   * @param to The array to store into
   * @param fromSize The size of the `from` array
   */
  void takeEvens(const float *from, float *to, size_t fromSize, WINDOW_FUNCTION window = nullptr);

  /**
   * Gets the value of a Hann window function at sample `n` of sample count `N`
   * @param n The current sample
   * @param N The total sample count
   * @return The normalized magnitude of the current sample
   */
  float windowHann(unsigned int n, unsigned int N);

  /**
   * Calculates the magnitudes of a series of complex numbers, then converts to dB (log)
   * @param magnitudes The magnitude output array
   * @param re Array of the real part of a series of complex numbers
   * @param im Array of the imaginary part of a series of complex numbers
   * @param len The length of the arrays
   */
  void calculateMagnitudesLog(float *magnitudes, const float *re, const float *im, size_t len);

  /**
   * Calculates the raw magnitudes of a series of complex numbers
   * @param magnitudes The magnitude output array
   * @param re Array of the real part of a series of complex numbers
   * @param im Array of the imaginary part of a series of complex numbers
   * @param len The length of the arrays
   */
  void calculateMagnitudes(float *magnitudes, const float *re, const float *im, size_t len);

}

#endif //PSLIGHTDASH_MATH_H
