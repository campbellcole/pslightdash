//
// Created by campbell on 6/10/2021.
//

#ifndef PSLIGHTDASH_BASERENDERTARGET_H
#define PSLIGHTDASH_BASERENDERTARGET_H

#include "gl/glrendertargetbuilder.h"
#include "gl/glrendertarget.h"

namespace dash::impl {
  class BaseRenderTarget {
  protected:
    GLRenderTarget *_instance;
    virtual GLRenderTarget *build() = 0;
  public:
    ~BaseRenderTarget() { delete _instance; }
    GLRenderTarget *getInstance() {
      if (!_instance) this->_instance = this->build();
      return this->_instance;
    }
  };
}


#endif //PSLIGHTDASH_BASERENDERTARGET_H
