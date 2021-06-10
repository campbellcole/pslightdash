//
// Created by campbell on 6/7/2021.
//

#ifndef PSLIGHTDASH_GLRENDERTARGETBUILDER_H
#define PSLIGHTDASH_GLRENDERTARGETBUILDER_H

#include "gl/glshader.h"
#include "gl/glrendertarget.h"
#include "dbg.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include <string>
#include <functional>
#include <vector>

namespace dash {
  class GLRenderTargetBuilder {
  private:
    bool named = false;
    bool textured = false;
    bool preBuffered = false;
    bool dynamicDraw = false;
    bool hasShader = false;
    bool hasRenderFunction = false;
    bool hasVAOFunction = false;
    bool hasRenderData = false;
    std::string _name;
    // Texture *texture;
    unsigned int _VBO = 0, _VAO = 0, _EBO = 0;
    GLShader *_shader;
    std::function<void(GLRenderTarget*)> _render;
    std::function<void()> _registerVAO;
    float *_vertices;
    unsigned int *_indices;
    unsigned int _vertexCount, _indexCount;
  public:
    GLRenderTargetBuilder();
    GLRenderTargetBuilder *withName(std::string name);
    GLRenderTargetBuilder *withTexture(/*Texture *texture*/); // TODO: implement this + texture class
    GLRenderTargetBuilder *withBuffers(unsigned int VBO, unsigned int VAO, unsigned int EBO);
    GLRenderTargetBuilder *usingDynamicDraw(unsigned int vertexCount, unsigned int indexCount);
    GLRenderTargetBuilder *withShader(GLShader *shader);
    GLRenderTargetBuilder *withRenderFunction(std::function<void(GLRenderTarget*)> render);
    GLRenderTargetBuilder *withVAORegisterFunction(std::function<void()> registerVAO);
    GLRenderTargetBuilder *withRenderData(float *vertices, unsigned int *indices, unsigned int vertexCount, unsigned int indexCount);
    GLRenderTarget *build();
  };
}


#endif //PSLIGHTDASH_GLRENDERTARGETBUILDER_H
