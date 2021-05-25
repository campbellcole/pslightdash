#ifndef RENDER_PROGRAM_HPP
#define RENDER_PROGRAM_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>

#include "utils.hpp"
#include "dbg.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

  void use();

  void setBoolU(const std::string &name, bool value);

  void setFloatU(const std::string &name, float value);

  void setIntU(const std::string &name, int value);

  void setFVec2U(const std::string &name, float x, float y);
};

#endif // RENDER_PROGRAM_HPP
