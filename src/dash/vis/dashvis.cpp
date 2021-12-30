//
// Created by Campbell Cole on 12/28/21.
//

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "primitives/primitives.h"

#include "dash/vis/audio_sdl.h"
#include "dash/vis/decode.h"

#include "dash/vis/dashvis.h"

static std::function<void(audio_ctx*, uint8_t*, int)> audioUpdate = [](audio_ctx*,uint8_t*, int){};

namespace dash::impl {
  DashVis::DashVis() {
    this->fft = new audiofft::AudioFFT();
    this->fft->init(SAMPLES_PER_UPDATE);
    this->complexSize = audiofft::AudioFFT::ComplexSize(SAMPLES_PER_UPDATE);
    debug("Initialized FFT with %zu samples per update and %zu frequency bands", SAMPLES_PER_UPDATE, this->complexSize - 1);
    this->re = new std::vector<float>(complexSize);
    this->im = new std::vector<float>(complexSize);
    if (!sdl_audio_init(&this->render, 44100, 2, 1, 0)) {
      log_err("Failed to initialize audio device");
    }
    audioUpdate = [this](audio_ctx *ctx, uint8_t* stream, int bytes){
      //auto len = bytes/sizeof(mp3d_sample_t);
      //auto *fstream = (float*)stream;
      this->fft->fft((float*)stream, this->re->data(), this->im->data());
      //debug("%d: %f %d %d %d", len, fstream[0], stream[len/2+1], stream[len/2+2], stream[len/2+3]);
    };
    sdl_set_callback([](audio_ctx *ctx, uint8_t *stream, int len) {
      audioUpdate(ctx, stream, len);
    });
    this->model = glm::mat4(1.0f);
    this->view = glm::mat4(1.0f);
    this->projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  }

  DashVis::~DashVis() {
    delete this->fft;
    this->fft = nullptr;
    delete this->re;
    delete this->im;
    this->re = this->im = nullptr;
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
        dash::primitives::TEXTURED_CUBE.vertices,
        dash::primitives::TEXTURED_CUBE.indices,
        dash::primitives::TEXTURED_CUBE.vertexCount,
        dash::primitives::TEXTURED_CUBE.indexCount
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

        for (unsigned int x = 0; x < 256; x++) {
          //for (unsigned int z = 0; z < 10; z++) {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(x * 0.25, 0.0, 0.0));
            target->getShader()->setUMat4F("model", model);

            //if (this->dec) {
              target->getShader()->setUVec2F("fft", (*this->re)[complexSize - x],(*this->im)[x]);
            /*} else {
              target->getShader()->setUVec2F("fft", 0,0);
            }*/

            glDrawElements(GL_TRIANGLES, dash::primitives::TEXTURED_CUBE.indexCount, GL_UNSIGNED_INT, 0);
          //}
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