//
// Created by campbell on 5/30/2021.
//

#ifndef PSLIGHTDASH_GLRENDERTARGET_H
#define PSLIGHTDASH_GLRENDERTARGET_H

#include "gl/glshader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <functional>
#include <vector>
#include <utility>

namespace dash {
  class GLRenderTarget {
  private:
    bool enabled;
    std::string name;
    // Texture *texture;
    unsigned int VBO, VAO, EBO;
    GLShader *shader;
    std::function<void()> renderFunc, registerVAO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
  public:
    explicit GLRenderTarget(std::string name);
    //GLRenderTarget* withShader(Shader *shader);
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] bool isEnabled() const;
    [[nodiscard]] GLShader *getShader();
    void render(GLFWwindow *window);
  };
}


#endif //PSLIGHTDASH_GLRENDERTARGET_H
