//
// Created by campbell on 6/16/2021.
//

#include "dash/text.h"

namespace dash::impl {
  Text::Text(GLFont *font, std::string text, float x, float y, float scale, glm::vec3 color)
    : font(font), text(std::move(text)), x(x), y(y), scale(scale), color(color) {}

  void Text::setText(std::string _text) {
    this->text = std::move(_text);
  }

  GLRenderTarget *Text::build() {
    GLRenderTargetBuilder builder;
    auto built = builder.withBuffers(this->font->getVBO(), this->font->getVAO(), this->font->getEBO())
      .withShader(GLFont::getDefaultShader()).withRenderFunction([this](GLRenderTarget *target) {
        float tX = this->x;
        float tY = this->y;

        target->getShader()->setUVec3F("textColor", this->color);

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(target->getVAO());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, target->getEBO());
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(DEFAULT_INDICES), DEFAULT_INDICES);

        std::string::const_iterator c;
        for (c = this->text.begin(); c != this->text.end(); c++) {
          Character ch = font->getCharacters()->at(*c);

          float xPos = tX + (ch.bearing.x * scale);
          float yPos = tY - ((ch.size.y - ch.bearing.y) * scale);

          float w = ch.size.x * scale;
          float h = ch.size.y * scale;

          float vertices[]{
            xPos, yPos + h, 0.0f, 0.0f,
            xPos, yPos, 0.0f, 1.0f,
            xPos + w, yPos, 1.0f, 1.0f,
            xPos + w, yPos + h, 1.0f, 0.0f
          };

          glBindTexture(GL_TEXTURE_2D, ch.textureID);
          glBindBuffer(GL_ARRAY_BUFFER, target->getVBO());
          glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

          glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
          tX += (ch.advance >> 6) * scale;
        }
      })
      .build();
    return built;
  }
}