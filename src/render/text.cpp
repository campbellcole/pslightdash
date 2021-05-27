//
// Created by campbell on 5/26/2021.
//

#include "render/text.h"

Text::Text(Font *font, const std::string &text, float x, float y, float scale, glm::vec3 color) : Renderable(
    ("text-" + text),
    false,
    GLYPH_VERTEX_COUNT,
    nullptr,
    GLYPH_INDEX_COUNT,
    nullptr,
    true,
    false,
    &Font::GLYPH_VAO_REGISTER,
    Font::getFontShader()),
    font(font), text(text), x(x), y(y), scale(scale), color(color) {
  this->VBO = font->getVBO();
  this->VAO = font->getVAO();
  this->EBO = font->getEBO();
}

Text::~Text() {
  Renderable::~Renderable();
}

void Text::render(RenderContext *context) {
  Shader *shader = Font::getFontShader();

  float tX = x;
  float tY = y;

  shader->use();
  shader->setFVec3U("textColor", color);
  shader->setFloatU("uTime", glfwGetTime());
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);

  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++) {
    Character ch = font->getCharacters()->at(*c);

    float xpos = tX + ch.bearing.x * scale;
    float ypos = tY - (ch.size.y - ch.bearing.y) * scale;

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

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    tX += (ch.advance >> 6) * scale;
  }
}