//
// Created by campbell on 11/18/2021.
//

#ifndef PSLIGHTDASH_TEST3D_H
#define PSLIGHTDASH_TEST3D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "baserendertarget.h"

namespace dash::impl {
  class Test3D: public BaseRenderTarget {
  private:
    glm::mat4 model, view, projection;
    glm::vec4 cubePositions[10] = {
      glm::vec4( 0.0f,  0.0f,  0.0f, 0.0f),
      glm::vec4( 2.0f,  5.0f, -15.0f, 0.0f),
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