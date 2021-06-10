//
// Created by campbell on 5/27/2021.
//

#ifndef PSLIGHTDASH_GLFONT_H
#define PSLIGHTDASH_GLFONT_H

#include <string>

#include "gl/glcontext.h"

namespace dash {
  class GLFont {
    GLFont(const std::string &name, int size, GLContext *glContext);
  };
}

#endif //PSLIGHTDASH_GLFONT_H
