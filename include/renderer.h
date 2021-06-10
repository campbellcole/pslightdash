//
// Created by campbell on 5/27/2021.
//

#ifndef PSLIGHTDASH_RENDERER_H
#define PSLIGHTDASH_RENDERER_H

#define DEFAULT_CONTEXT GLContext

#include "pslightdashconfig.h"
#include "gl/glcontext.h"

namespace dash {
  class Renderer {
  private:
    int width, height;
    GLContext *context;
    bool manageContext = false;
  public:
    explicit Renderer(GLContext *context);
    Renderer(int width, int height);
    Renderer();
    ~Renderer();
    void initialize();
    void renderTargets();
    GLContext *getContext();
    void start();
  };
}


#endif //PSLIGHTDASH_RENDERER_H
