#ifndef RENDER_TEXTURE_HPP
#define RENDER_TEXTURE_HPP

#include <string>

#include "utils.hpp"
#include "dbg.h"
#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture {
private:
  unsigned int texture;
public:
  Texture(const std::string &filename);

  unsigned int getTextureID();
};

#endif // RENDER_TEXTURE_HPP
