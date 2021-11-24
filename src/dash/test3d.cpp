//
// Created by campbell on 11/18/2021.
//

#include "dash/test3d.h"

namespace dash::impl {

  GLRenderTarget *Test3D::build() {
    unsigned int indices[] = {
      0,1,2,
      2,3,0,
      4,5,6,
      6,7,4,
      8,9,10,
      10,4,8,
      11,2,12,
      12,13,11,
      10,14,5,
      5,4,10,
      3,2,11,
      11,15,3
    };
    float vertices[] = {
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, //0
      0.5f, -0.5f, -0.5f,  1.0f, 0.0f, //1
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f, //2
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, //3
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, //4
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,//5
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,//6
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,//7
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,//8
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,//9
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,//10
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,//11
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,//12
      0.5f, -0.5f,  0.5f,  0.0f, 0.0f,//13
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,//14
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,//15
    };
    unsigned int vertexCount = 80, indexCount = 36;
    GLRenderTargetBuilder targetBuilder;
    auto built = targetBuilder.withName("3d")
      .withVAORegisterFunction([] {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
      }).withRenderData(vertices, indices, vertexCount, indexCount)
      .withRenderFunction([this, indexCount](GLRenderTarget *target) {
        this->direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        this->direction.y = sin(glm::radians(this->pitch));
        this->direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        this->cameraFront = glm::normalize(this->direction);
        this->view = glm::lookAt(this->cameraPos, this->cameraPos + this->cameraFront, this->cameraUp);

        target->getShader()->setUMat4F("view", this->view);
        target->getShader()->setUMat4F("projection", this->projection);

        glBindTexture(GL_TEXTURE_2D, target->getTexture()->getTextureID());
        glBindVertexArray(target->getVAO());

        for (unsigned int i = 0; i < 10; i++) {
          auto model = glm::mat4(1.0f);
          model = glm::translate(model, glm::vec3(cubePositions[i]));
          cubePositions[i].w += 0.1 * (i + 1);
          model = glm::rotate(model, glm::radians(cubePositions[i].w), glm::vec3(1.0f, 0.3f, 0.5f));

          target->getShader()->setUMat4F("model", model);
          glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        }
      }).withKeypressCheckFunction([this](GLFWwindow *window, float delta) {
        float movementDelta = this->CAMERA_SPEED * delta;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
          this->cameraPos += movementDelta * this->cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
          this->cameraPos -= movementDelta * this->cameraFront;
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
      })
      .withTexture()
      .build();
    return built;
  }

  Test3D::Test3D() {
    this->model = glm::mat4(1.0f);
    this->view = glm::mat4(1.0f);
    this->projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  }
}