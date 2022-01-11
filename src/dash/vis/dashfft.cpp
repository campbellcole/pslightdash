//
// Created by Campbell Cole on 1/9/22.
//

#include "dash/vis/dashfft.h"

#include <SDL2/SDL.h>

#include "util/math.h"
#include "utils.h"
#include "dbg.h"

namespace dash::impl {

  static std::function<void(audio_ctx*,uint8_t*,int)> audioUpdate = [](audio_ctx*,uint8_t*, int){};

  DashFFT::DashFFT() {
    if (!sdl_audio_init(&this->render, 44100, 2, 1, this->samplesPerUpdate)) {
      log_err("Failed to initialize audio device");;
    }
    this->samplesPerUpdate = 8192;
    this->workingSamples = this->samplesPerUpdate / 2;
    this->fft = new audiofft::AudioFFT();
    this->fft->init(this->workingSamples);
    this->complexSize = audiofft::AudioFFT::ComplexSize(this->workingSamples);
    this->re = new std::vector<float>(this->complexSize);
    this->im = new std::vector<float>(this->complexSize);
    this->buffers = new float*[2]{
      new float[this->workingSamples]{0},
      new float[this->workingSamples]{0}
    };
    this->workingBuffer = new float[this->workingSamples]{0};
    this->magnitudes = new float[this->complexSize]{0};
    audioUpdate = [this](audio_ctx *ctx, const uint8_t *stream, int bytes){
      //debug("bytes: %d | adjusted: %llu", bytes, bytes/sizeof(mp3d_sample_t));
      if (!stream) return;
      int len = bytes/sizeof(mp3d_sample_t);
      auto *fstream = reinterpret_cast<const float*>(stream);
      int toAdd = fmin(this->workingSamples - this->bufferLens[this->currentBuffer], len);
      int excess = len - toAdd;
      ::memcpy(this->buffers[this->currentBuffer] + this->bufferLens[this->currentBuffer], fstream, toAdd);
      this->bufferLens[this->currentBuffer] += toAdd;
      if (excess > 0) {
        util::math::takeEvens(this->buffers[this->currentBuffer], this->workingBuffer, this->workingSamples, util::math::windowHann);
        //util::math::combArray(this->buffers[this->currentBuffer], this->workingBuffer, WORKING_SAMPLES, util::math::windowHann, 1);
        this->fft->fft(this->workingBuffer, this->re->data(), this->im->data());
        util::math::calculateMagnitudes(this->magnitudes, this->re->data(), this->im->data(), complexSize);
        this->bufferLens[this->currentBuffer] = 0;
        std::fill(this->buffers[this->currentBuffer], this->buffers[this->currentBuffer] + this->workingSamples, 0);
        this->currentBuffer = !this->currentBuffer;
        ::memcpy(this->buffers[this->currentBuffer], fstream, excess);
        this->bufferLens[this->currentBuffer] += excess;
      }
      sdl_set_callback([](audio_ctx *ctx, uint8_t *stream, int len) { // i have to do this roundabout method because C doesn't support captures
        audioUpdate(ctx, stream, len);
      });
      //debug("%f %f %f %f %f", this->magnitudes[0], this->magnitudes[1], this->magnitudes[2], this->magnitudes[3], this->magnitudes[4]);
    };
  }

  DashFFT::~DashFFT() {
    delnptr(this->re);
    delnptr(this->im);
    delanptr(this->buffers[0]);
    delanptr(this->buffers[1]);
    delanptr(this->workingBuffer);
    delanptr(this->magnitudes);
    delnptr(this->fft);
  }

  bool DashFFT::loadMP3(const std::string &filename) {
    debug("Playing...");
    sdl_audio_set_dec(this->render, 0);
    if (!open_dec(&this->dec, getResourcePath(filename).c_str())) {
      log_err("Failed to decode file");
      return false;
    }
    sdl_audio_set_dec(this->render, &this->dec);
    this->playing = true;
    return true;
  }

  /**
   * Starts or stops audio device from requesting more data from callback
   * @param playing The new state to attempt to start
   * @return
   */
  bool DashFFT::setPlaying(bool playing) {
    if (!this->render) {
      log_err("No audio device, cannot change play state");
      return false;
    }
    SDL_PauseAudioDevice(((audio_ctx*)this->render)->dev, playing);
    this->playing = playing;
    return this->playing;
  }

  /**
   * Toggle playing an MP3, if any is playing
   * @return the new play state (might not change)
   */
  bool DashFFT::togglePlaying() {
    return this->setPlaying(!this->playing);
  }

  size_t DashFFT::getComplexSize() {
    return this->complexSize;
  }

  float *DashFFT::getMagnitudes() {
    return this->magnitudes;
  }

}