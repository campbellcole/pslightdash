//
// Created by Campbell Cole on 12/28/21.
//

#ifndef PSLIGHTDASH_DASHVIS_H
#define PSLIGHTDASH_DASHVIS_H

#include <vector>

#include "dash/vis/AudioFFT.h"

#include "dash/baserendertarget.h"
#include "dash/vis/decode.h"
#include "dash/vis/audio_sdl.h"
#include "primitives/primitives.h"

namespace dash::impl {
  class DashVis: public BaseRenderTarget {
  private:
    audiofft::AudioFFT *fft;
    bool playing = false;
    void *render;
    decoder dec;
    double lastPlayToggle;
    float sideLength = 0.0;
    GLShape pointShape = primitives::TEXTURED_CUBE(0.01, sideLength);
    const float CAMERA_SPEED = 3.5f, MOUSE_SENSITIVITY = 0.1f;
    static const size_t SAMPLES_PER_UPDATE = 16384 / 2;
    size_t complexSize;
    float *streamRight, *magnitudes;
    float lastX = 0.0f, lastY = 0.0f, pitch = 0.0f, yaw = -90.0f;
    glm::mat4 /*model,*/ view, projection;
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f),
      cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f),
      cameraDirection = glm::normalize(cameraPos - cameraTarget),
      up = glm::vec3(0.0f, 1.0f, 0.0f),
      cameraRight = glm::normalize(glm::cross(up, cameraDirection)),
      cameraUp = glm::cross(cameraDirection, cameraRight),
      cameraFront = glm::vec3(0.0f, 0.0f, -1.0f),
      direction = glm::vec3(0.0f, 0.0f, 0.0f);
    std::vector<float> *re, *im = re = nullptr;
  public:
    DashVis();
    ~DashVis();
    GLRenderTarget *build() override;
  };
}


#endif //PSLIGHTDASH_DASHVIS_H
