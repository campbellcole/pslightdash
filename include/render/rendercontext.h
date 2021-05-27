#ifndef RENDER_RENDERCONTEXT_HPP
#define RENDER_RENDERCONTEXT_HPP

#include <list>
#include <algorithm>
#include <string>

#include "dbg.h"
#include "render/shader.h"
#include "render/renderable.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Renderable;

void _handleResize(GLFWwindow *window, int width, int height);

class RenderContext {
private:
  int width, height;
  std::list<Renderable *> targets;

  void processInput(GLFWwindow *);

public:
  GLFWwindow *window;

  RenderContext(int width, int height);

  ~RenderContext();

  int getWidth();

  int getHeight();

  void handleResize(GLFWwindow *window, int width, int height);

  void addTarget(Renderable *target);

  void insertTarget(Renderable *target, int index);

  // todo: see which of these functions is actually useful and remove the others
  void removeTarget(Renderable *target);

  void removeTarget(int index);

  void removeTarget(const std::string &targetName);

  // end todo
  std::list<Renderable *> getTargets();
};

#endif // RENDER_RENDERCONTEXT_HPP
