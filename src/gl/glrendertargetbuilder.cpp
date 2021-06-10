//
// Created by campbell on 6/7/2021.
//

#include "gl/glrendertargetbuilder.h"

namespace dash {

  GLRenderTargetBuilder::GLRenderTargetBuilder() {}

  GLRenderTargetBuilder *GLRenderTargetBuilder::withName(std::string name) {
    this->named = true;
    this->name = name;
    return this;
  }

  GLRenderTargetBuilder *GLRenderTargetBuilder::withTexture() {
    return this;
  }

  GLRenderTargetBuilder *GLRenderTargetBuilder::withBuffers(unsigned int VBO, unsigned int VAO, unsigned int EBO) {
    this->VBO = VBO;
    this->VAO = VAO;
    this->EBO = EBO;
    this->preBuffered = true;
    return this;
  }

  GLRenderTargetBuilder *GLRenderTargetBuilder::usingDynamicDraw() {
    this->dynamicDraw = true;
    return this;
  }

  GLRenderTargetBuilder *GLRenderTargetBuilder::withShader(GLShader *shader) {
    this->hasShader = true;
    this->shader = shader;
    return this;
  }

  GLRenderTargetBuilder *GLRenderTargetBuilder::withRenderFunction(std::function<void()> render) {
    this->hasRenderFunction = true;
    this->render = render;
    return this;
  }

  GLRenderTargetBuilder *GLRenderTargetBuilder::withVAORegisterFunction(std::function<void()> registerVAO) {
    this->hasVAOFunction = true;
    this->registerVAO = registerVAO;
    return this;
  }

  GLRenderTargetBuilder *
  GLRenderTargetBuilder::withRenderData(std::vector<float> vertices, std::vector<unsigned int> indices) {
    this->vertices = vertices;
    this->indices = indices;
    return this;
  }

  GLRenderTarget *GLRenderTargetBuilder::build() {
    return nullptr;
  }

}