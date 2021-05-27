//
// Created by campbell on 5/26/2021.
//

#ifndef PSLIGHTDASH_TEXT_H
#define PSLIGHTDASH_TEXT_H

#include <string>

#include "render/font.h"
#include "render/renderable.h"

class Font;

class Text: public Renderable {
private:
  Font *font;
  const std::string text;
  float x, y, scale;
  glm::vec3 color;
public:
  Text(Font *font, const std::string &text, float x, float y, float scale, glm::vec3 color);
  ~Text();
  void render(RenderContext *context);
};


#endif //PSLIGHTDASH_TEXT_H
