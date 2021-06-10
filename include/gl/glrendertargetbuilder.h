//
// Created by campbell on 6/7/2021.
//

#ifndef PSLIGHTDASH_GLRENDERTARGETBUILDER_H
#define PSLIGHTDASH_GLRENDERTARGETBUILDER_H

#include <string>
#include <functional>
#include <vector>

#include "glshader.h"
#include "glrendertarget.h"

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
    std::string name;
    // Texture *texture;
    unsigned int VBO, VAO, EBO;
    GLShader *shader;
    std::function<void()> render, registerVAO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
  public:
    GLRenderTargetBuilder();
    GLRenderTargetBuilder *withName(std::string name);
    GLRenderTargetBuilder *withTexture(/*Texture *texture*/); // TODO: implement this + texture class
    GLRenderTargetBuilder *withBuffers(unsigned int VBO, unsigned int VAO, unsigned int EBO);
    GLRenderTargetBuilder *usingDynamicDraw();
    GLRenderTargetBuilder *withShader(GLShader *shader);
    GLRenderTargetBuilder *withRenderFunction(std::function<void()> render);
    GLRenderTargetBuilder *withVAORegisterFunction(std::function<void()> registerVAO);
    GLRenderTargetBuilder *withRenderData(std::vector<float> vertices, std::vector<unsigned int> indices);
    GLRenderTarget *build();
  };
}


#endif //PSLIGHTDASH_GLRENDERTARGETBUILDER_H
