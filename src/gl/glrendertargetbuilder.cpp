//
// Created by campbell on 6/7/2021.
//

#include "gl/glrendertargetbuilder.h"

namespace dash {

  GLRenderTargetBuilder::GLRenderTargetBuilder() {}

  GLRenderTargetBuilder GLRenderTargetBuilder::withName(std::string name) {
    this->named = true;
    this->_name = std::move(name);
    return *this;
  }

  GLRenderTargetBuilder GLRenderTargetBuilder::withTexture(GLTexture *texture) {
    this->textured = true;
    this->_texture = texture;
    return *this;
  }

  GLRenderTargetBuilder GLRenderTargetBuilder::withBuffers(unsigned int VBO, unsigned int VAO, unsigned int EBO) {
    this->preBuffered = true;
    this->_VBO = VBO;
    this->_VAO = VAO;
    this->_EBO = EBO;
    return *this;
  }

  GLRenderTargetBuilder GLRenderTargetBuilder::usingDynamicDraw(unsigned int vertexCount, unsigned int indexCount) {
    this->dynamicDraw = true;
    this->_vertexCount = vertexCount;
    this->_indexCount = indexCount;
    return *this;
  }

  GLRenderTargetBuilder GLRenderTargetBuilder::withShader(GLShader *shader) {
    this->hasShader = true;
    this->_shader = shader;
    return *this;
  }

  GLRenderTargetBuilder GLRenderTargetBuilder::withRenderFunction(std::function<void(GLRenderTarget*)> render) {
    this->hasRenderFunction = true;
    this->_render = std::move(render);
    return *this;
  }

  GLRenderTargetBuilder GLRenderTargetBuilder::withKeypressCheckFunction(std::function<void(GLFWwindow*, float)> checkKeypress) {
    this->hasKeypressCheckFunction = true;
    this->_checkKeypress = std::move(checkKeypress);
    return *this;
  }
  GLRenderTargetBuilder GLRenderTargetBuilder::withMouseMovementCallback(std::function<void(GLFWwindow*,double,double)> onMouseMove) {
    this->hasMouseMovementCallback = true;
    this->_onMouseMove = onMouseMove;
    return *this;
  }

  GLRenderTargetBuilder GLRenderTargetBuilder::withVAORegisterFunction(std::function<void()> registerVAO) {
    this->hasVAOFunction = true;
    this->_registerVAO = std::move(registerVAO);
    return *this;
  }

  GLRenderTargetBuilder
  GLRenderTargetBuilder::withRenderData(float *vertices, unsigned int *indices, unsigned int vertexCount, unsigned int indexCount) {
    this->hasRenderData = true;
    this->_vertices = vertices;
    this->_indices = indices;
    this->_vertexCount = vertexCount;
    this->_indexCount = indexCount;
    return *this;
  }

  GLRenderTarget *GLRenderTargetBuilder::build() { // needs some work lul
    if (!this->preBuffered) {
      if (!this->dynamicDraw && !this->hasRenderData) {
        log_err("Must either provide pre made buffers or vertex data to create the buffers with static draw");
        return nullptr;
      }
      GLenum usage = dynamicDraw ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
      glGenVertexArrays(1, &this->_VAO);
      glBindVertexArray(this->_VAO);
      glGenBuffers(1, &this->_VBO);
      glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
      if (this->_vertices) {
        glBufferData(GL_ARRAY_BUFFER, this->_vertexCount * sizeof(float), this->_vertices, usage);
      } else {
        if (!this->dynamicDraw) {
          log_err("Cannot create a static draw target with no input vertices");
          return nullptr;
        }
        glBufferData(GL_ARRAY_BUFFER, this->_vertexCount * sizeof(float), nullptr, usage);
      }
      glGenBuffers(1, &this->_EBO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_EBO);
      if (this->_indices) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_indexCount * sizeof(unsigned int), this->_indices, usage);
      } else {
        if (!this->dynamicDraw) {
          log_err("Cannot create a static draw target with no input indices");
          return nullptr;
        }
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_indexCount * sizeof(unsigned int), nullptr, usage);
      }
      if (!this->hasVAOFunction) {
        log_err("Target needs a VAO register function if buffers are not pre made");
        return nullptr;
      } else this->_registerVAO();
    }
    if (!this->hasRenderFunction) { // TODO: implement default render function
      log_err("Cannot create a target without a render function (TODO: implement defaults later)");
      return nullptr;
    }
    if (!this->hasKeypressCheckFunction) {
      this->_checkKeypress = [](GLFWwindow *window, float delta){};
    }
    if (!this->hasMouseMovementCallback) {
      this->_onMouseMove = [](GLFWwindow *window, double x, double y){};
    }
    if (!this->hasShader) { // TODO: implement default shader (with default uniforms)
      if (this->named) {
        this->_shader = new GLShader(this->_name);
      } else {
        log_err("Cannot create an unnamed target without a shader (TODO: implement defaults later)");
        return nullptr;
      }
    }
    if (this->textured && !this->_texture) {
      if (!this->named) {
        log_err("Cannot load a default texture without a target name");
        return nullptr;
      }
      this->_texture = new GLTexture(this->_name);
    }
    auto _instance = new GLRenderTarget(_name, _VBO, _VAO, _EBO, dynamicDraw, !preBuffered, _shader, _texture, _render, _checkKeypress, _onMouseMove, _vertices, _indices, _vertexCount, _indexCount);
    return _instance;
  }

}