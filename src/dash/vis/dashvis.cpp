//
// Created by Campbell Cole on 12/28/21.
//

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "dash/vis/dashvis.h"

namespace dash::impl {

  void DashVis::toggleMouseCapture() {
    this->captureEnabled = !this->captureEnabled;
    glfwSetInputMode(this->window, GLFW_CURSOR, this->captureEnabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
  }

  DashVis::DashVis(GLFWwindow *window, impl::Text *statusTarget) : window(window), statusTarget(statusTarget) {
    this->fft = new impl::DashFFT();
    this->magnitudesLen = this->fft->getComplexSize();
    //this->model = glm::mat4(1.0f);
    this->view = glm::mat4(1.0f);
    this->projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  }

  DashVis::~DashVis() {
    delete this->fft;
    this->fft = nullptr;
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
        target->getShader()->setUInt("bands", this->magnitudesLen);

        glBindTexture(GL_TEXTURE_2D, target->getTexture()->getTextureID());
        glBindVertexArray(target->getVAO());
        //glBindBuffer(GL_UNIFORM_BUFFER, this->FFTBuffer);
        //glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(this->magnitudes), this->magnitudes);

        for (int x = 0; x < this->magnitudesLen; x++) {
          auto model = glm::mat4(1.0f);
          model = glm::translate(model, glm::vec3(0.0, 1.0, 0.0));
          target->getShader()->setUMat4F("model", model);

          target->getShader()->setUFloat("fft", this->fft->getMagnitudes()[x]);
          target->getShader()->setUInt("pos", x);

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
            this->statusTarget->setText(
              this->fft->togglePlaying() ?
              "playing" : "paused");
            break;
          case GLFW_KEY_L:
            this->statusTarget->setText(
              this->fft->loadMP3("test.mp3") ?
              "playing" : "failed to load");
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