//
// Created by campbell on 5/27/2021.
//

#ifndef PSLIGHTDASH_RENDERER_H
#define PSLIGHTDASH_RENDERER_H

#include "pslightdashconfig.h"
#include "context.h"

namespace dash {
  class Renderer {
  private:
    int width, height;
    Context *context;
  public:
    Renderer(int width, int height, Context *context);
    Renderer(int width, int height);
    Renderer();
    ~Renderer();
    void initialize();
    Context *getContext();
    void start();
  };
}


#endif //PSLIGHTDASH_RENDERER_H
