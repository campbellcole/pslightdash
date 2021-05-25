#ifndef RENDER_RENDERER_HPP
#define RENDER_RENDERER_HPP

#include <vector>

#include "discordhooker.hpp"
#include "pslightdash.hpp"
#include "dbg.h"
#include "render/program.hpp"
#include "render/rendercontext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class RenderContext;

class Renderer {
private:
  RenderContext *context;
public:
  Renderer(RenderContext *context);

  ~Renderer();

  void renderTargets();

  void handleInput(GLFWwindow *window);

  void begin();
};

#endif // RENDER_RENDERER_HPP
