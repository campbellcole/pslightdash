//
// Created by campbell on 5/30/2021.
//

#include "gl/glshader.h"

namespace dash {
  void GLShader::setDefaultUniforms(GLShader *shader, glm::vec2 resolution) {
    shader->setUFloat("uTime", glfwGetTime()); // todo: find a good place to put this
    shader->setUVec2F("uResolution", resolution.x, resolution.y);
  }

  GLShader::GLShader(std::string name)
      : GLShader(name, (name + "_vertex.glsl"), (name + "_fragment.glsl")) {}

  GLShader::GLShader(std::string name, std::string vertexFilename, std::string fragmentFilename) {
    std::string vertexShader, fragmentShader;
    std::ifstream readStream;

    readStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::string vertexShaderPath = getResourcePath(SHADER_PATH_PREFIX + vertexFilename);
    std::string fragmentShaderPath = getResourcePath(SHADER_PATH_PREFIX + fragmentFilename);

    try {
      readStream.open(vertexShaderPath);
      std::stringstream vertStream;
      vertStream << readStream.rdbuf();
      readStream.close();
      vertexShader = vertStream.str();
    } catch (std::ifstream::failure &e) {
      log_err("Failed to read \"%s\" vertex shader: %s (Error %d: %s)", name.c_str(), vertexShaderPath.c_str(), e.code().value(), e.code().message().c_str());
    }

    try {
      readStream.open(fragmentShaderPath);
      std::stringstream fragStream;
      fragStream << readStream.rdbuf();
      readStream.close();
      fragmentShader = fragStream.str();
    } catch (std::ifstream::failure &e) {
      log_err("Failed to read \"%s\" fragment shader: %s (Error %d: %s)", name.c_str(), fragmentShaderPath.c_str(), e.code().value(), e.code().message().c_str());
    }

    const char *cstrVert = vertexShader.c_str();
    const char *cstrFrag = fragmentShader.c_str();
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &cstrVert, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
      log_err("Failed to compile \"%s\" vertex shader: %s (Error: %s)", name.c_str(), vertexShaderPath.c_str(), infoLog);
    } else debug("Successfully compiled vertex shader: %s", vertexShaderPath.c_str());

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &cstrFrag, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
      log_err("Failed to compile \"%s\" fragment shader: %s (Error: %s)", name.c_str(), fragmentShaderPath.c_str(), infoLog);
    } else debug("Successfully compiled fragment shader: %s", fragmentShaderPath.c_str());

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      log_err("Failed to link program: %d (Error: %s)", ID, infoLog);
    } else debug("Successfully linked vertex and fragment shaders.");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  GLShader::~GLShader() {
    glDeleteProgram(ID);
  }

  void GLShader::use() const {
    glUseProgram(ID);
  }

  void GLShader::setUBool(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
  }

  void GLShader::setUFloat(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }

  void GLShader::setUVec2F(const std::string &name, float x, float y) {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
  }

  void GLShader::setUVec2F(const std::string &name, glm::vec2 &value) {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
  }

  void GLShader::setUVec3F(const std::string &name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
  }

  void GLShader::setUVec3F(const std::string &name, glm::vec3 &value) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
  }

  void GLShader::setUMat4F(const std::string &name, glm::mat4 &value) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
  }
}