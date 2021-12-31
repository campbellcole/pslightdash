//
// Created by campbell on 5/30/2021.
//

#include "gl/glrendertarget.h"

namespace dash::gl {
  GLRenderTarget::GLRenderTarget(
    std::string name,
    unsigned int VBO,
    unsigned int VAO,
    unsigned int EBO,
    bool dynamicDraw,
    bool manageBuffers,
    GLShader *shader,
    GLTexture *texture,
    std::function<void(GLRenderTarget *)> render,
    std::function<void(GLFWwindow *,float)> checkKeyPress,
    std::function<void(GLFWwindow*,int,int,int,int)> onKeyPress,
    std::function<void(GLFWwindow *,double,double)> onMouseMove,
    float *vertices,
    unsigned int *indices,
    unsigned int vertexCount,
    unsigned int indexCount)
    : _enabled(true),
      _name(std::move(name)),
      _VBO(VBO),
      _VAO(VAO),
      _EBO(EBO),
      _dynamicDraw(dynamicDraw),
      _manageBuffers(manageBuffers),
      _shader(shader),
      _texture(texture),
      _checkKeyPress(std::move(checkKeyPress)),
      _onKeyPress(std::move(onKeyPress)),
      _render(std::move(render)),
      _onMouseMove(std::move(onMouseMove)),
      _vertices(vertices),
      _indices(indices),
      _vertexCount(vertexCount),
      _indexCount(indexCount) {}

  GLRenderTarget::~GLRenderTarget() {
    if (this->_manageBuffers) {
      glDeleteBuffers(1, &this->_VBO);
      glDeleteBuffers(1, &this->_EBO);
      glDeleteVertexArrays(1, &this->_VAO);
    }
    if (!this->_dynamicDraw) {
      delete this->_shader;
      this->_shader = nullptr;
    }
  }

  const std::string &GLRenderTarget::getName() const {
    return this->_name;
  }

  bool GLRenderTarget::isEnabled() const {
    return this->_enabled;
  }

  void GLRenderTarget::setEnabled(bool enabled) {
    this->_enabled = enabled;
  }

  GLShader *GLRenderTarget::getShader() {
    return this->_shader;
  }

  GLTexture *GLRenderTarget::getTexture() {
    return this->_texture;
  }

  unsigned int GLRenderTarget::getVBO() const {
    return this->_VBO;
  }

  unsigned int GLRenderTarget::getVAO() const {
    return this->_VAO;
  }

  unsigned int GLRenderTarget::getEBO() const {
    return this->_EBO;
  }

  void GLRenderTarget::render(GLFWwindow *window) {
    if (this->isEnabled()) {
      this->_render(this);
    }
  }

  void GLRenderTarget::render(GLFWwindow *window, float *vertices, unsigned int *indices, unsigned int vertexCount,
                              unsigned int indexCount) {
    this->_vertices = vertices;
    this->_indices = indices;
    this->_vertexCount = vertexCount;
    this->_indexCount = indexCount;
    this->render(window);
  }

  void GLRenderTarget::checkKeyPress(GLFWwindow *window, float delta) {
    if (this->isEnabled()) {
      this->_checkKeyPress(window, delta);
    }
  }

  void GLRenderTarget::onKeyPress(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (this->isEnabled()) {
      this->_onKeyPress(window, key, scancode, action, mods);
    }
  }

  void GLRenderTarget::onMouseMove(GLFWwindow *window, double x, double y) {
    if (this->isEnabled()) {
      this->_onMouseMove(window, x, y);
    }
  }

}