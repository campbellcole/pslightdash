//
// Created by campbell on 6/7/2021.
//

#ifndef PSLIGHTDASH_GLRENDERTARGETBUILDER_H
#define PSLIGHTDASH_GLRENDERTARGETBUILDER_H

#include "gl/glshader.h"
#include "gl/glrendertarget.h"
#include "gl/gltexture.h"
#include "dbg.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>
#include <functional>
#include <vector>
#include <utility>
#include <primitives/primitives.h>

namespace dash::gl {
  class GLRenderTargetBuilder {
  private:
    bool named = false;
    bool textured = false;
    bool preBuffered = false;
    bool dynamicDraw = false;
    bool hasShader = false;
    bool hasRenderFunction = false;
    bool hasKeypressCheckFunction = false;
    bool hasMouseMovementCallback = false;
    bool hasVAOFunction = false;
    bool hasRenderData = false;
    std::string _name;
    GLTexture *_texture;
    unsigned int _VBO = 0, _VAO = 0, _EBO = 0;
    GLShader *_shader;
    std::function<void(GLRenderTarget*)> _render;
    std::function<void(GLFWwindow*,float)> _checkKeypress;
    std::function<void(GLFWwindow*,double,double)> _onMouseMove;
    std::function<void()> _registerVAO;
    float *_vertices;
    unsigned int *_indices;
    unsigned int _vertexCount, _indexCount;
  public:
    GLRenderTargetBuilder();
    GLRenderTargetBuilder withName(std::string name);
    GLRenderTargetBuilder withTexture(GLTexture *texture = nullptr);
    GLRenderTargetBuilder withBuffers(unsigned int VBO, unsigned int VAO, unsigned int EBO);
    GLRenderTargetBuilder usingDynamicDraw(unsigned int vertexCount, unsigned int indexCount);
    GLRenderTargetBuilder withShader(GLShader *shader);
    GLRenderTargetBuilder withRenderFunction(std::function<void(GLRenderTarget*)> render);
    GLRenderTargetBuilder withKeypressCheckFunction(std::function<void(GLFWwindow*, float)> checkKeypress);
    GLRenderTargetBuilder withMouseMovementCallback(std::function<void(GLFWwindow*,double,double)> onMouseMove);
    GLRenderTargetBuilder withVAORegisterFunction(std::function<void()> registerVAO);
    GLRenderTargetBuilder withRenderData(float *vertices, unsigned int *indices, unsigned int vertexCount, unsigned int indexCount);
    GLRenderTargetBuilder withRenderData(GLShape primitive);
    GLRenderTarget *build();
  };
}


#endif //PSLIGHTDASH_GLRENDERTARGETBUILDER_H
