//
// Created by campbell on 5/30/2021.
//

#include "gl/glrendertarget.h"

namespace dash {
  GLRenderTarget::GLRenderTarget(std::string name) : name(std::move(name)) {}

  const std::string& GLRenderTarget::getName() const {
    return this->name;
  }

  bool GLRenderTarget::isEnabled() const {
    return this->enabled;
  }

  GLShader *GLRenderTarget::getShader() {
    return this->shader;
  }

  void GLRenderTarget::render(GLFWwindow *window) {

  }
}