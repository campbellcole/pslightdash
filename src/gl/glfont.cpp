//
// Created by campbell on 5/27/2021.
//

#include "gl/glfont.h"

namespace dash {
  GLShader *GLFont::defaultFontShader = nullptr;

  GLShader *GLFont::getDefaultShader() {
    if (!GLFont::defaultFontShader) {
      GLFont::defaultFontShader = new GLShader("font");
      glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(pslightdash_WINDOW_WIDTH),
                                        0.0f, static_cast<float>(pslightdash_WINDOW_HEIGHT));
      GLFont::defaultFontShader->use();
      GLFont::defaultFontShader->setUMat4F("projection", projection);
    }
    return GLFont::defaultFontShader;
  }

  GLFont::GLFont(const std::string &name, int textSize) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
      log_err("Failed to initialize FreeType");
      return;
    }

    FT_Face face;
    if (FT_New_Face(
        ft,
        getResourcePath("font/" + name + ".ttf").c_str(),
        0,
        &face
    )) {
      log_err("Could not load font: %s", name.c_str());
      return;
    }

    FT_Set_Pixel_Sizes(face, 0, textSize);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (unsigned char c = 0; c < 128; c++) {
      if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
        log_err("Failed to load glyph: %c", c);
        continue;
      }

      unsigned int texture;
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexImage2D(
          GL_TEXTURE_2D,
          0,
          GL_RED,
          face->glyph->bitmap.width,
          face->glyph->bitmap.rows,
          0,
          GL_RED,
          GL_UNSIGNED_BYTE,
          face->glyph->bitmap.buffer
      );

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      Character character = {
          texture,
          glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
          glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
          face->glyph->advance.x
      };

      characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * GLYPH_VERTEX_COUNT, nullptr, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * GLYPH_INDEX_COUNT, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
  }

  GLFont::~GLFont() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
  }

  unsigned int GLFont::getVAO() {
    return this->VAO;
  }

  unsigned int GLFont::getVBO() {
    return this->VBO;
  }

  unsigned int GLFont::getEBO() {
    return this->EBO;
  }

  const std::map<char, Character> *GLFont::getCharacters() {
    return &this->characters;
  }
}