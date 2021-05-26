#ifndef RENDER_RENDERER_HPP
#define RENDER_RENDERER_HPP

#include <vector>

#include "discordhooker.h"
#include "pslightdash.h"
#include "dbg.h"
#include "render/program.h"
#include "render/rendercontext.h"
#include "render/font.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class RenderContext;

class Renderer {
private:
  RenderContext *context;
public:
  Renderer(int width, int height);

  ~Renderer();

  RenderContext* getContext();

  void renderTargets();

  void handleInput(GLFWwindow *window);

  void begin();
};

#endif // RENDER_RENDERER_HPP
