//
// Created by campbell on 5/30/2021.
//

#ifndef PSLIGHTDASH_GLRENDERTARGET_H
#define PSLIGHTDASH_GLRENDERTARGET_H

#include "gl/glshader.h"
#include "gl/gltexture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <functional>
#include <vector>
#include <utility>

namespace dash {
  class GLRenderTarget {
  protected:
    bool _enabled, _dynamicDraw, _manageBuffers;
    std::string _name;
    unsigned int _VBO, _VAO, _EBO;
    GLShader *_shader;
    GLTexture *_texture;
    std::function<void(GLRenderTarget*)> _renderFunc;
    float *_vertices;
    unsigned int *_indices;
    unsigned int _vertexCount, _indexCount;
  public:
    GLRenderTarget(
        std::string name,
        unsigned int VBO,
        unsigned int VAO,
        unsigned int EBO,
        bool dynamicDraw,
        bool manageBuffers,
        GLShader *shader,
        GLTexture *texture,
        std::function<void(GLRenderTarget*)> render,
        float *vertices,
        unsigned int *indices,
        unsigned int vertexCount,
        unsigned int indexCount);
    ~GLRenderTarget();
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] bool isEnabled() const;
    void setEnabled(bool enabled);
    [[nodiscard]] GLShader *getShader();
    [[nodiscard]] GLTexture *getTexture();
    [[nodiscard]] unsigned int getVBO() const;
    [[nodiscard]] unsigned int getVAO() const;
    [[nodiscard]] unsigned int getEBO() const;
    void render(GLFWwindow *window) ;
    void render(GLFWwindow *window, float *vertices, unsigned int *indices, unsigned int vertexCount, unsigned int indexCount);
  };
}


#endif //PSLIGHTDASH_GLRENDERTARGET_H
