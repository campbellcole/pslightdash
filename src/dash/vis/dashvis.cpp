//
// Created by Campbell Cole on 12/28/21.
//

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "dash/vis/audio_sdl.h"
#include "dash/vis/decode.h"

#include "dash/vis/dashvis.h"

static std::function<void(audio_ctx*, uint8_t*, int)> audioUpdate = [](audio_ctx*,uint8_t*, int){};

namespace dash::impl {
  DashVis::DashVis() {
    this->fft = new audiofft::AudioFFT();
    this->fft->init(SAMPLES_PER_UPDATE / 2);
    this->complexSize = audiofft::AudioFFT::ComplexSize(SAMPLES_PER_UPDATE / 2);
    debug("Initialized FFT with %zu samples per update and %zu frequency bands", SAMPLES_PER_UPDATE, this->complexSize - 1);
    this->re = new std::vector<float>(complexSize);
    this->im = new std::vector<float>(complexSize);
    this->streamRight = new float[SAMPLES_PER_UPDATE / 2]{};
    this->magnitudes = new float[complexSize]{};
    if (!sdl_audio_init(&this->render, 44100, 2, 1, 0)) {
      log_err("Failed to initialize audio device");;
    }
    audioUpdate = [this](audio_ctx *ctx, uint8_t stream[], int bytes){
      //auto len = bytes/sizeof(mp3d_sample_t);
      //debug("len: %d | sizeof(float): %lu | len/so(f): %lu", bytes, sizeof(float), bytes/sizeof(float));
      if (!stream) return;
      auto *fstream = reinterpret_cast<float*>(stream);
      for (size_t i = 0, r = 0; i < bytes/sizeof(mp3d_sample_t) - 1; i+=2, r++) { // take every other sample for channels and pass through Hann window
        this->streamRight[r] = fstream[i] * powf(sinf(3.141593f * i / (SAMPLES_PER_UPDATE / 2)), 2);
      }
      this->fft->fft(this->streamRight, this->re->data(), this->im->data());
      for (size_t i = 0; i < complexSize; i++) {
        this->magnitudes[i] = 10 * log10(((*this->re)[i] * (*this->re)[i]) + ((*this->im)[i] * (*this->im)[i]));
      }
      //debug("%d: %f %d %d %d", len, fstream[0], stream[len/2+1], stream[len/2+2], stream[len/2+3]);
    };
    sdl_set_callback([](audio_ctx *ctx, uint8_t *stream, int len) {
      audioUpdate(ctx, stream, len);
    });
    //this->model = glm::mat4(1.0f);
    this->view = glm::mat4(1.0f);
    this->projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  }

  DashVis::~DashVis() {
    delete this->fft;
    this->fft = nullptr;
    delete this->re;
    delete this->im;
    this->re = this->im = nullptr;
    delete this->streamRight;
    delete this->magnitudes;
    this->streamRight = nullptr;
    this->magnitudes = nullptr;
    //sdl_audio_release(&this->render); // causes sigabrt
  }

  GLRenderTarget *DashVis::build() {
    GLRenderTargetBuilder builder;
    auto built = builder.withName("vis")
      .withVAORegisterFunction([]{
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
      }).withRenderData(
        this->pointShape.vertices,
        this->pointShape.indices,
        this->pointShape.vertexCount,
        this->pointShape.indexCount
      ).withRenderFunction([this](GLRenderTarget *target){
        this->direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        this->direction.y = sin(glm::radians(this->pitch));
        this->direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        this->cameraFront = glm::normalize(this->direction);
        this->view = glm::lookAt(this->cameraPos, this->cameraPos + this->cameraFront, this->cameraUp);

        target->getShader()->setUMat4F("view", this->view);
        target->getShader()->setUMat4F("projection", this->projection);

        glBindTexture(GL_TEXTURE_2D, target->getTexture()->getTextureID());
        glBindVertexArray(target->getVAO());

        for (int x = 0; x < this->complexSize; x++) {
          auto model = glm::mat4(1.0f);
          model = glm::translate(model, glm::vec3(x * (sideLength / 2), 0.0, 0.0));
          target->getShader()->setUMat4F("model", model);

          target->getShader()->setUFloat("fft", this->magnitudes[x]);
          target->getShader()->setUInt("pos", x);

          glDrawElements(GL_TRIANGLES, this->pointShape.indexCount, GL_UNSIGNED_INT, 0);
        }
      }).withKeypressCheckFunction([this](GLFWwindow *window, float delta){
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
          if ((glfwGetTime() - this->lastPlayToggle) > 1.0) {
            if (!this->playing) {
              debug("Playing... %x", this->render);
              sdl_audio_set_dec(this->render, 0);
              if (!open_dec(&this->dec, getResourcePath("test.mp3").c_str())) {
                log_err("Failed to decode file");
              }
              sdl_audio_set_dec(this->render, &this->dec);
              this->playing = true;
            } else {
              sdl_audio_set_dec(this->render, 0);
              this->playing = false;
            }
            this->lastPlayToggle = glfwGetTime();
          }
        }
        float movementDelta = this->CAMERA_SPEED * delta * ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) ? 3.0 : 1.0);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
          this->cameraPos += movementDelta * glm::vec3(this->direction.x, 0.0, this->direction.z);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
          this->cameraPos -= movementDelta * glm::vec3(this->direction.x, 0.0, this->direction.z);;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
          this->cameraPos += movementDelta * this->cameraUp;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
          this->cameraPos -= movementDelta * this->cameraUp;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
          this->cameraPos -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * movementDelta;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
          this->cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * movementDelta;
      }).withMouseMovementCallback([this](GLFWwindow *window, double x, double y) {
        this->yaw += (x - this->lastX) * this->MOUSE_SENSITIVITY;
        this->pitch += (this->lastY - y) * this->MOUSE_SENSITIVITY;
        this->lastX = x;
        this->lastY = y;
        if (this->pitch > 89.0f)
          this->pitch = 89.0f;
        if (this->pitch < -89.0f)
          this->pitch = -89.0f;
      }).withTexture().build();
    return built;
  }
}