//
// Created by campbell on 6/9/2021.
//

#ifndef PSLIGHTDASH_TESTRENDERTARGET_H
#define PSLIGHTDASH_TESTRENDERTARGET_H

#include "gl/glrendertarget.h"
#include "gl/glrendertargetbuilder.h"

#include "dash/baserendertarget.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include <vector>

namespace dash::impl {
  class TestRenderTarget : public BaseRenderTarget {
    GLRenderTarget *build() override;
  };
}


#endif //PSLIGHTDASH_TESTRENDERTARGET_H
