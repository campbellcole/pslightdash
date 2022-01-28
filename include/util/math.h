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
   * @param window The window function (if any) to apply to the dataset
   */
  void takeEvens(const float *from, float *to, size_t fromSize, unsigned int step = 2, WINDOW_FUNCTION window = nullptr);

  /**
   * Takes the `from` array, and appends every other element to the second half of `to`.
   * <br>
   * Example: [0, 0, 1, 1, 2, 2] -> [0, 1, 2, 0, 1, 2]
   * @param from The array to take from
   * @param to The array to store into
   * @param fromSize The size of the `from` array
   * @param window The window function (if any) to apply to the dataset using the mode `windowMode`
   * @param windowMode How to apply the window function. 0 will set N to fromSize and run the window function on the entire array. 1 will effectively apply two window functions, joining the two halves at zero.
   *
   */
  void combArray(const float *from, float *to, size_t fromSize, WINDOW_FUNCTION window = nullptr, int windowMode = 0);

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
