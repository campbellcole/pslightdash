//
// Created by Campbell Cole on 12/28/21.
//

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "util/math.h"

#include "dash/vis/audio_sdl.h"
#include "dash/vis/decode.h"

#include "dash/vis/dashvis.h"

static std::function<void(audio_ctx*, uint8_t*, int)> audioUpdate = [](audio_ctx*,uint8_t*, int){};

namespace dash::impl {

  void DashVis::toggleMouseCapture() {
    this->captureEnabled = !this->captureEnabled;
    glfwSetInputMode(this->window, GLFW_CURSOR, this->captureEnabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
  }

  DashVis::DashVis(GLFWwindow *window, impl::Text *statusTarget) : window(window), statusTarget(statusTarget) {
    this->fft = new audiofft::AudioFFT();
    this->fft->init(SAMPLES_PER_UPDATE);
    this->complexSize = audiofft::AudioFFT::ComplexSize(SAMPLES_PER_UPDATE);
    debug("Initialized FFT with %zu samples per update and %zu frequency bands", SAMPLES_PER_UPDATE, this->complexSize - 1);
    this->re = new std::vector<float>(complexSize);
    this->im = new std::vector<float>(complexSize);
    this->streamRight = new float[SAMPLES_PER_UPDATE]{};
    this->magnitudes = new float[complexSize]{};

    if (!sdl_audio_init(&this->render, 44100, 2, 1, 0)) {
      log_err("Failed to initialize audio device");;
    }
    audioUpdate = [this](audio_ctx *ctx, const uint8_t *stream, int bytes){
      if (!stream) return;
      auto *fstream = reinterpret_cast<const float*>(stream);
      util::math::combArray(fstream, this->streamRight, bytes/sizeof(mp3d_sample_t), util::math::windowHann, 1);
      this->fft->fft(this->streamRight, this->re->data(), this->im->data());
      util::math::calculateMagnitudes(this->magnitudes, this->re->data(), this->im->data(), complexSize);
      //debug("%f %f %f %f %f", this->magnitudes[0], this->magnitudes[1], this->magnitudes[2], this->magnitudes[3], this->magnitudes[4]);
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
      .withVAORegisterFunction([this]{
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
        //glBindBuffer(GL_UNIFORM_BUFFER, this->FFTBuffer);
        //glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(this->magnitudes), this->magnitudes);

        for (int x = 0; x < this->complexSize; x++) {
          auto model = glm::mat4(1.0f);
          model = glm::translate(model, glm::vec3((x / 2) * (sideLength / 2), 0.0, x % 2));
          target->getShader()->setUMat4F("model", model);

          target->getShader()->setUFloat("fft", this->magnitudes[x]);
          target->getShader()->setUInt("pos", x / 2);

          glDrawElements(GL_TRIANGLES, this->pointShape.indexCount, GL_UNSIGNED_INT, 0);
        }
      }).withKeypressCheckFunction([this](GLFWwindow *window, float delta){
        float movementDelta = this->CAMERA_SPEED * delta * ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) ? 3.0 : 1.0);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
          this->cameraPos += movementDelta * this->direction;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
          this->cameraPos -= movementDelta * this->direction;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
          this->cameraPos += movementDelta * this->cameraUp;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
          this->cameraPos -= movementDelta * this->cameraUp;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
          this->cameraPos -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * movementDelta;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
          this->cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * movementDelta;
      }).withKeypressCallback([this](GLFWwindow *window, int key, int scancode, int action, int mods){
        if (action != GLFW_PRESS) return; // if GLFW_RELEASE or GLFW_REPEAT (aka holding the key), skip
        switch (key) {
          case GLFW_KEY_P:
            if (!this->playing) {
              debug("Playing...");
              sdl_audio_set_dec(this->render, 0);
              if (!open_dec(&this->dec, getResourcePath("test.mp3").c_str())) {
                log_err("Failed to decode file");
              }
              sdl_audio_set_dec(this->render, &this->dec);
              this->playing = true;
              this->statusTarget->setText("playing");
            } else {
              sdl_audio_set_dec(this->render, 0);
              this->playing = false;
              this->statusTarget->setText("paused");
            }
            break;
          case GLFW_KEY_M:
            this->toggleMouseCapture();
            break;
          default:
            break;
        }
      }).withMouseMovementCallback([this](GLFWwindow *window, double x, double y) {
        if (!this->captureEnabled) return;
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