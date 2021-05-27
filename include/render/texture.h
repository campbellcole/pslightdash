#ifndef RENDER_TEXTURE_HPP
#define RENDER_TEXTURE_HPP

#include <string>

#include "utils.h"
#include "dbg.h"
#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class BasicTexture {
private:
  unsigned int texture;
public:
  BasicTexture(const std::string &filename);

  unsigned int getTextureID();
};

#endif // RENDER_TEXTURE_HPP
