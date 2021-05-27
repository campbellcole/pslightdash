#include "render/shader.h"

Shader::Shader(const std::string &name) : name(name) {
  std::string vertexShader, fragmentShader;
  std::ifstream vertFileStream, fragFileStream;

  std::stringstream vFilename, fFilename;

  vFilename << name << "_vertex.glsl";
  fFilename << name << "_fragment.glsl";

  std::string vertexShaderPath = getResourcePath("glsl/" + vFilename.str());
  std::string fragmentShaderPath = getResourcePath("glsl/" + fFilename.str());

  debug("Attempting to load shader: %s", name.c_str());

  vertFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fragFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    vertFileStream.open(vertexShaderPath);
    std::stringstream ssVertShader;
    ssVertShader << vertFileStream.rdbuf();
    vertFileStream.close();
    vertexShader = ssVertShader.str();
  }
  catch (std::ifstream::failure e) {
    log_err(FORMAT_SHADER_READ_ERROR, "vertex", vertexShaderPath.c_str(), e.code().value(), e.code().message().c_str());
  }

  try {
    fragFileStream.open(fragmentShaderPath);
    std::stringstream ssFragShader;
    ssFragShader << fragFileStream.rdbuf();
    fragFileStream.close();
    fragmentShader = ssFragShader.str();
  }
  catch (std::ifstream::failure e) {
    log_err(FORMAT_SHADER_READ_ERROR, "fragment", fragmentShaderPath.c_str(), e.code().value(),
            e.code().message().c_str());
  }

  const char *cstrVert = vertexShader.c_str();
  const char *cstrFrag = fragmentShader.c_str();
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &cstrVert, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    log_err(FORMAT_SHADER_COMPILE_ERROR, "vertex", vertexShaderPath.c_str(), infoLog);
  } else
    debug("Successfully compiled vertex shader.");

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &cstrFrag, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    log_err(FORMAT_SHADER_COMPILE_ERROR, "fragment", fragmentShaderPath.c_str(), infoLog);
  } else
    debug("Successfully compiled fragment shader.");

  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);

  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    log_err(FORMAT_PROGRAM_LINK_ERROR, ID, infoLog);
  } else
    debug("Successfully linked vertex and fragment shaders.");

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

Shader::~Shader() {
  glDeleteProgram(ID);
}

void Shader::use() {
  glUseProgram(ID);
}

void Shader::setBoolU(const std::string &name, bool value) {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}

void Shader::setFloatU(const std::string &name, float value) {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setIntU(const std::string &name, int value) {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFVec2U(const std::string &name, float x, float y) {
  glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setFVec3U(const std::string &name, glm::vec3 value) {
  glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::setFVec3U(const std::string &name, float x, float y, float z) {
  glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setFMat4U(const std::string &name, glm::mat4 &value) {
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}