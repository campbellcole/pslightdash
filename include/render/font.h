//
// Created by campbell on 5/26/2021.
//

#ifndef PSLIGHTDASH_FONT_H
#define PSLIGHTDASH_FONT_H

#include <glad/glad.h>

#include <string>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "utils.h"
#include "dbg.h"
#include "pslightdashconfig.h"
#include "render/program.h"

struct Character {
  unsigned int textureID;
  glm::ivec2 size;
  glm::ivec2 bearing;
  long advance;
};

class Font {
private:
  std::map<char, Character> characters;
  Program *program;
  unsigned int VAO, VBO, EBO;
public:
  Font(const std::string &name, int size);
  ~Font();
  void draw(std::string text, float x, float y, float scale, glm::vec3 color);
};

#endif //PSLIGHTDASH_FONT_H
