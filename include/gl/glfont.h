//
// Created by campbell on 5/27/2021.
//

#ifndef PSLIGHTDASH_GLFONT_H
#define PSLIGHTDASH_GLFONT_H

#include <map>
#include <string>

#include "pslightdashconfig.h"
#include "gl/glshader.h"
#include "utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#define GLYPH_VERTEX_COUNT 16
#define GLYPH_INDEX_COUNT 6

namespace dash::gl {

  struct Character {
    unsigned int textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    long advance;
  };

  class GLFont {
  private:
    static GLShader *defaultFontShader;
    std::map<char, Character> characters;
    unsigned int VAO, VBO, EBO;
  public:
    static GLShader *getDefaultShader();

    GLFont(const std::string &name, int textSize);

    ~GLFont();

    unsigned int getVAO();

    unsigned int getVBO();

    unsigned int getEBO();

    const std::map<char, Character> *getCharacters();
  };
}

#endif //PSLIGHTDASH_GLFONT_H
