//
// Created by campbell on 5/30/2021.
//

#ifndef PSLIGHTDASH_GLSHADER_H
#define PSLIGHTDASH_GLSHADER_H

#define SHADER_PATH_PREFIX "glsl/"

#include "utils.h"
#include "dbg.h"

#include <string>
#include <utility>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

namespace dash::gl {
  class GLShader {
  private:
    unsigned int ID;
  public:
    static void setDefaultUniforms(GLShader *shader, glm::vec2 resolution);

    explicit GLShader(std::string name);

    GLShader(std::string name, std::string vertexFilename, std::string fragmentFilename);

    ~GLShader();

    void use() const;

    void setUBool(const std::string &name, bool value);

    void setUInt(const std::string &name, int value);

    void setUFloat(const std::string &name, float value);

    void setUFloatArr(const std::string &name, float *value, int len);

    void setUVec2F(const std::string &name, float x, float y);

    void setUVec2F(const std::string &name, glm::vec2 &value);

    void setUVec3F(const std::string &name, float x, float y, float z);

    void setUVec3F(const std::string &name, glm::vec3 &value);

    void setUMat4F(const std::string &name, glm::mat4 &value);
  };
}

#endif //PSLIGHTDASH_GLSHADER_H
