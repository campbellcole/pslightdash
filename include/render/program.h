#ifndef RENDER_PROGRAM_HPP
#define RENDER_PROGRAM_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>

#include "utils.h"
#include "dbg.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define FORMAT_SHADER_READ_ERROR "Failed to read %s shader: %s\nError %d: %s\n"
#define FORMAT_SHADER_COMPILE_ERROR "Failed to compile %s shader: %s\nError: %s\n"
#define FORMAT_PROGRAM_LINK_ERROR "Failed to link program: %d\nError: %s\n"

class Program {
private:
  unsigned int ID;
public:
  const std::string name;

  Program(const std::string &name);

  ~Program();

  void use() const;

  void setBoolU(const std::string &name, bool value) const;

  void setFloatU(const std::string &name, float value) const;

  void setIntU(const std::string &name, int value) const;

  void setFVec2U(const std::string &name, float x, float y) const;

  void setFVec3U(const std::string &name, glm::vec3 value) const;

  void setFVec3U(const std::string &name, float x, float y, float z) const;

  void setFMat4U(const std::string &name, glm::mat4 &value) const;
};

#endif // RENDER_PROGRAM_HPP
