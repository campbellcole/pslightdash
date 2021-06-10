//
// Created by campbell on 5/30/2021.
//

#include "gl/glrendertarget.h"

namespace dash {
  GLRenderTarget::GLRenderTarget(
      std::string name,
      unsigned int VBO,
      unsigned int VAO,
      unsigned int EBO,
      bool dynamicDraw,
      bool manageBuffers,
      GLShader *shader,
      std::function<void(GLRenderTarget*)> render,
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
        _renderFunc(std::move(render)),
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
      this->_renderFunc(this);
    }
  }

  void GLRenderTarget::render(GLFWwindow *window, float *vertices, unsigned int *indices, unsigned int vertexCount, unsigned int indexCount) {
    this->_vertices = vertices;
    this->_indices = indices;
    this->_vertexCount = vertexCount;
    this->_indexCount = indexCount;
    this->render(window);
  }

}