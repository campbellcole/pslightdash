//
// Created by campbell on 5/27/2021.
//

#include "renderer.h"

namespace dash {
  Renderer::Renderer(GLContext *context) : width(context->getWidth()), height(context->getHeight()), context(context) {}
  Renderer::Renderer(int width, int height) : width(width), height(height), context(nullptr) {}
  Renderer::Renderer() : Renderer(pslightdash_WINDOW_WIDTH, pslightdash_WINDOW_HEIGHT) {}
  Renderer::~Renderer() {
    if (manageContext) {
      delete context;
      context = nullptr;
    }
  }
  void Renderer::initialize() {
    if (!context) {
      manageContext = true;
      context = new DEFAULT_CONTEXT(width, height);
    }
    if (!context->initialized()) {
      context->initialize();
    }
  }

  void Renderer::start() {
    context->start();
  }
}