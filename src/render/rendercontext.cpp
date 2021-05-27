#include "render/rendercontext.h"

RenderContext::RenderContext(int width, int height) : width(width), height(height) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VERSION_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VERSION_MINOR);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  window = glfwCreateWindow(width, height, "PSLIGHTDASH", nullptr, nullptr);

  if (window == nullptr) {
    log_err("failed to create window");
    glfwTerminate();
    exit(1);
  }

  glfwSetWindowUserPointer(window, this);
  glfwSetFramebufferSizeCallback(window, _handleResize);

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    log_err("failed to initialize GLAD");
    glfwTerminate();
    exit(1);
  }

  glViewport(0, 0, width, height);
  //glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  log_info("Initialized OpenGL v%s", glGetString(GL_VERSION));
}

RenderContext::~RenderContext() {
  targets.clear();
}

int RenderContext::getWidth() {
  return width;
}

int RenderContext::getHeight() {
  return height;
}

void _handleResize(GLFWwindow *window, int width, int height) {
  ((RenderContext *) glfwGetWindowUserPointer(window))->handleResize(window, width, height);
}

void RenderContext::handleResize(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
  this->width = width;
  this->height = height;
}

void RenderContext::addTarget(Renderable *target) {
  targets.push_back(target);
}

void RenderContext::insertTarget(Renderable *target, int index) {
  targets.insert(std::next(targets.begin(), index), target);
}

void RenderContext::removeTarget(Renderable *target) {
  std::list<Renderable *>::iterator it;
  it = std::find(targets.begin(), targets.end(), target);
  if (it != targets.end())
    targets.erase(it);
  else
    debug("RenderContext attempted to remove a target that does not exist: %s", target->name.c_str());
}

void RenderContext::removeTarget(int index) {
}

void RenderContext::removeTarget(const std::string &targetName) {
  targets.remove_if([targetName](Renderable *target) {
    return target->name.compare(targetName) == 0;
  });
}

std::list<Renderable *> RenderContext::getTargets() {
  return targets;
}
