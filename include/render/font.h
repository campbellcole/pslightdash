//
// Created by campbell on 5/26/2021.
//

#ifndef PSLIGHTDASH_FONT_H
#define PSLIGHTDASH_FONT_H

#include "dbg.h"
#include "render/shader.h"
#include "utils.h"
#include "pslightdashconfig.h"
#include "render/renderable.h"
#include "render/text.h"

#include <string>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H

// (vec2, vec2) * 4
#define GLYPH_VERTEX_COUNT 16
// (vec3, vec3)
#define GLYPH_INDEX_COUNT 6

struct Character {
  unsigned int textureID;
  glm::ivec2 size;
  glm::ivec2 bearing;
  long advance;
};

class Text;

class Font {
private:
  static Shader* fontShader;
  std::map<char, Character> characters;
  unsigned int VAO, VBO, EBO;
public:
  static void GLYPH_VAO_REGISTER();
  static Shader* getFontShader();
  Font(const std::string &name, int size);
  ~Font();
  unsigned int getVAO();
  unsigned int getVBO();
  unsigned int getEBO();
  const std::map<char, Character>* getCharacters();
  Text *drawText(std::string text, float x, float y, float scale, glm::vec3 color);
};

#endif //PSLIGHTDASH_FONT_H
