//
// Created by campbell on 11/18/2021.
//

#ifndef PSLIGHTDASH_TEST3D_H
#define PSLIGHTDASH_TEST3D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "baserendertarget.h"
#include "primitives/primitives.h"

namespace dash::impl {
  class Test3D: public BaseRenderTarget {
  private:
    const float CAMERA_SPEED = 3.5f, MOUSE_SENSITIVITY = 0.1f;
    float lastX = 0.0f, lastY = 0.0f, pitch = 0.0f, yaw = -90.0f;
    float sideLength = 0.0;
    GLShape cube = primitives::TEXTURED_CUBE(1.0, sideLength);
    glm::mat4 model, view, projection;
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f),
      cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f),
      cameraDirection = glm::normalize(cameraPos - cameraTarget),
      up = glm::vec3(0.0f, 1.0f, 0.0f),
      cameraRight = glm::normalize(glm::cross(up, cameraDirection)),
      cameraUp = glm::cross(cameraDirection, cameraRight),
      cameraFront = glm::vec3(0.0f, 0.0f, -1.0f),
      direction = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec4 cubePositions[10] = {
      glm::vec4( 0.0f,  0.0f,  0.0f, 0.0f),
      glm::vec4( 1.0f,  0.0f, 0.0f, 0.0f),
      glm::vec4(-1.5f, -2.2f, -2.5f, 0.0f),
      glm::vec4(-3.8f, -2.0f, -12.3f, 0.0f),
      glm::vec4( 2.4f, -0.4f, -3.5f, 0.0f),
      glm::vec4(-1.7f,  3.0f, -7.5f, 0.0f),
      glm::vec4( 1.3f, -2.0f, -2.5f, 0.0f),
      glm::vec4( 1.5f,  2.0f, -2.5f, 0.0f),
      glm::vec4( 1.5f,  0.2f, -1.5f, 0.0f),
      glm::vec4(-1.3f,  1.0f, -1.5f, 0.0f)
    };
  public:
    Test3D();
    GLRenderTarget *build() override;
  };
}


#endif //PSLIGHTDASH_TEST3D_H
