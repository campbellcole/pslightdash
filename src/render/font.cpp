//
// Created by campbell on 5/26/2021.
//

#include "render/font.h"

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
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, nullptr, GL_DYNAMIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, nullptr, GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);

  program = new Program("font");
  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(pslightdash_WINDOW_WIDTH), 0.0f,
                                    static_cast<float>(pslightdash_WINDOW_HEIGHT));
  program->use();
  program->setFMat4U("projection", projection);
}

Font::~Font() {
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);
  if (program) {
    delete program;
    program = nullptr;
  }
}

void Font::draw(std::string text, float x, float y, float scale, glm::vec3 color) {
  if (!program) return;

  program->use();
  program->setFVec3U("textColor", color);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);

  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++) {
    Character ch = characters[*c];

    float xpos = x + ch.bearing.x * scale;
    float ypos = y - (ch.size.y - ch.bearing.y) * scale;

    float w = ch.size.x * scale;
    float h = ch.size.y * scale;

    float vertices[] {
      xpos    , ypos + h, 0.0f, 0.0f,
      xpos    , ypos    , 0.0f, 1.0f,
      xpos + w, ypos    , 1.0f, 1.0f,
      xpos + w, ypos + h, 1.0f, 0.0f
    };

    unsigned int indices[] {
      0, 1, 2,
      0, 2, 3
    };

    glBindTexture(GL_TEXTURE_2D, ch.textureID);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    x += (ch.advance >> 6) * scale;
  }
}
