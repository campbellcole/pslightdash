//
// Created by campbell on 5/26/2021.
//

#include "render/font.h"

void Font::GLYPH_VAO_REGISTER() {
  /*
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);*/
  // do nothing, find an easier way to tell compiler to do nothing
}

Shader* Font::fontShader = nullptr; // could probably be inline but i don't want to accidentally recreate the shader

Shader* Font::getFontShader() {
  if (!Font::fontShader) {
    Font::fontShader = new Shader("font");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(pslightdash_WINDOW_WIDTH), 0.0f,
                                      static_cast<float>(pslightdash_WINDOW_HEIGHT));
    Font::fontShader->use();
    Font::fontShader->setFMat4U("projection", projection);
  }
  return Font::fontShader;
}

Font::Font(const std::string &name, int size) {
  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    log_err("Failed to initalize FreeType");
    return;
  }

  FT_Face face;
  if (FT_New_Face(
      ft,
      getResourcePath("font/" + name + ".ttf").c_str(),
      0,
      &face)) {
    log_err("Could not load font: %s", name.c_str());
    return;
  }

  FT_Set_Pixel_Sizes(face, 0, size);

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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

Font::~Font() {
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);
  if (Font::fontShader) {
    delete Font::fontShader;
    Font::fontShader = nullptr;
  }
}

Text* Font::drawText(std::string text, float x, float y, float scale, glm::vec3 color) {
  Text *target = new Text(this, text, x, y, scale, color);
  return target;
}

unsigned int Font::getVAO() {
  return VAO;
}

unsigned int Font::getVBO() {
  return VBO;
}

unsigned int Font::getEBO() {
  return EBO;
}

const std::map<char, Character>* Font::getCharacters() {
  return &characters;
}
