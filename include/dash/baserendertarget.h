//
// Created by campbell on 6/10/2021.
//

#ifndef PSLIGHTDASH_BASERENDERTARGET_H
#define PSLIGHTDASH_BASERENDERTARGET_H

#include "gl/glrendertargetbuilder.h"
#include "gl/glrendertarget.h"

using namespace dash::gl;

namespace dash::impl {
  class BaseRenderTarget {
  protected:
    GLRenderTarget *_instance = nullptr;
    virtual GLRenderTarget *build() = 0;
  public:
    ~BaseRenderTarget() { delete _instance; }
    GLRenderTarget *getInstance() {
      if (!this->_instance) this->_instance = this->build();
      return this->_instance;
    }
  };
}


#endif //PSLIGHTDASH_BASERENDERTARGET_H
