//
// Created by campbell on 5/27/2021.
//

#include "renderer.h"

namespace dash {
  Renderer::Renderer(int width, int height, Context *context) : width(width), height(height), context(context) {}
  Renderer::Renderer(int width, int height) : Renderer(width, height, nullptr) {}
  Renderer::Renderer() : Renderer(pslightdash_WINDOW_WIDTH, pslightdash_WINDOW_HEIGHT) {}
  Renderer::~Renderer() {
    if (context) {
      delete context;
      context = nullptr;
    }
  }
  void Renderer::initialize() {
    if (!context) {
      // initialize context
    }
  }
  void Renderer::start() {

  }
}