//
// Created by Campbell Cole on 12/28/21.
//

#ifndef PSLIGHTDASH_DASHVIS_H
#define PSLIGHTDASH_DASHVIS_H

#include <vector>
#include <map>

#include "dash/vis/AudioFFT.h"

#include "dash/baserendertarget.h"
#include "dash/text.h"

#include "dash/vis/decode.h"
#include "dash/vis/audio_sdl.h"

#include "primitives/primitives.h"

#include <GLFW/glfw3.h>

namespace dash::impl {
  class DashVis: public BaseRenderTarget {
  private:
    GLFWwindow *window;
    std::map<int, int> lastPressStates{};
    impl::Text *statusTarget;
    audiofft::AudioFFT *fft;
    bool playing = false;
    void *render;
    decoder dec;
    float sideLength = 0.0;
    GLShape pointShape = primitives::TEXTURED_CUBE(0.1, sideLength);
    const float CAMERA_SPEED = 3.5f, MOUSE_SENSITIVITY = 0.1f;
    int SAMPLES_PER_UPDATE;
    int WORKING_SAMPLES;
    size_t complexSize;
    float **buffers;
    float *workingBuffer;
    int bufferLens[2] = {0,0};
    size_t currentBuffer = 0;
    float *magnitudes;
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
    bool captureEnabled = true;
    void toggleMouseCapture();
  public:
    DashVis(GLFWwindow *window, impl::Text *statusTarget);
    ~DashVis();
    GLRenderTarget *build() override;
  };
}


#endif //PSLIGHTDASH_DASHVIS_H
