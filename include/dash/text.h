//
// Created by campbell on 6/16/2021.
//

#ifndef PSLIGHTDASH_TEXT_H
#define PSLIGHTDASH_TEXT_H

#include <string>
#include <utility>

#include "gl/glfont.h"
#include "gl/glcontext.h"
#include "gl/glrendertargetbuilder.h"
#include "dash/baserendertarget.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

using dash::gl::GLFont;

namespace dash::impl {
  class Text : public BaseRenderTarget {
  private:
    GLFont *font;
    const std::string text;
    float x, y, scale;
    glm::vec3 color;
    const int DEFAULT_INDICES[6] {0, 1, 2, 0, 2, 3};
  public:
    Text(GLFont *font, std::string text, float x, float y, float scale, glm::vec3 color);
    GLRenderTarget *build() override;
  };
}


#endif //PSLIGHTDASH_TEXT_H
