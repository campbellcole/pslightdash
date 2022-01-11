//
// Created by Campbell Cole on 1/9/22.
//

#ifndef PSLIGHTDASH_DASHFFT_H
#define PSLIGHTDASH_DASHFFT_H

#include <string>
#include <vector>
#include <functional>

#include "dash/vis/AudioFFT.h"
#include "dash/vis/audio_sdl.h"
#include "primitives/primitives.h"

namespace dash::impl {

  class DashFFT {
  private:
    audiofft::AudioFFT *fft;
    std::vector<float> *re, *im = re = nullptr;
    decoder dec;
    void *render;
    float sideLength = 0.0;
    int samplesPerUpdate;
    int workingSamples;
    size_t complexSize;
    float **buffers;
    float *workingBuffer;
    int bufferLens[2] = {0,0};
    size_t currentBuffer = 0;
    float *magnitudes;
    bool playing = false;
  public:
    DashFFT();
    ~DashFFT();

    bool loadMP3(const std::string &filename);

    bool setPlaying(bool playing);

    bool togglePlaying();

    size_t getComplexSize();

    /**
     * Length is this.getComplexSize()
     * @return the magnitudes array
     */
    float* getMagnitudes();
  };
}

#endif //PSLIGHTDASH_DASHFFT_H
