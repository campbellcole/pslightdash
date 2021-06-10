//
// Created by campbell on 5/27/2021.
//

#include "gl/glcontext.h"

namespace dash {
  GLContext::GLContext(unsigned int width, unsigned int height) : width(width), height(height) {}

  void GLContext::initialize() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    int iWidth = static_cast<int>(this->width);
    int iHeight = static_cast<int>(this->height);

    window = glfwCreateWindow(
        iWidth,
        iHeight,
        "",
        nullptr,
        nullptr);

    if (!window) {
      log_err("Failed to create GLFW window, terminating");
      glfwTerminate();
      exit(1);
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, GLContext::_handleResize);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
      log_err("Failed to initialize OpenGL");
      glfwTerminate();
      exit(1);
    }

    debug("viewport width: %d\nviewport height: %d", iWidth, iHeight);

    glViewport(0, 0, iWidth, iHeight);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    b_initialized = true;
    log_info("Initialized OpenGL v%s", glGetString(GL_VERSION));
  }

  int GLContext::getWidth() const {
    return this->width;
  }

  int GLContext::getHeight() const {
    return this->height;
  }

  bool GLContext::initialized() const {
    return this->b_initialized;
  }

  void GLContext::addTarget(GLRenderTarget *target) {
    targetsByShader.insert(std::make_pair(target->getShader(), target));
    //targets.push_back(target);
  }
/* hopefully it's practical to add elements in the right order
  void GLContext::insertTarget(GLRenderTarget *target, int position) {
    if ()
    targets.insert(std::next(targets.begin(), position), target);
  }
*/
  bool GLContext::removeTarget(const std::string &name) { // this can DEFINITELY be optimized
    for (std::pair<GLShader *const, GLRenderTarget *> pair : targetsByShader) {
      if (pair.second->getName() == name) {
        std::pair<map_iter, map_iter> iterpair = targetsByShader.equal_range(pair.first);
        auto it = iterpair.first;
        for (; it != iterpair.second; ++it) {
          if (it->second->getName() == name) {
            targetsByShader.erase(it);
            return true;
          }
        }
      }
    }
    return false;
  }

  void GLContext::_handleResize(GLFWwindow *window, int width, int height) {
    ((GLContext *)glfwGetWindowUserPointer(window))->handleResize(window, width, height); // must set user pointer
  }

  void GLContext::handleResize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
  }

  void GLContext::start() {
    while (!glfwWindowShouldClose(this->window)) {
      glClear(GL_COLOR_BUFFER_BIT);
      glClearColor(0.3, 0.0, 0.8, 1.0);

      for (map_iter it = targetsByShader.begin(), end = targetsByShader.end(); it != end; it = targetsByShader.upper_bound(it->first)) {
        std::pair<map_iter, map_iter> iterpair = targetsByShader.equal_range(it->first);
        it->first->use(); // activate shader
        GLShader::setDefaultUniforms(it->first, glm::vec2(this->getWidth(), this->getHeight()));
        auto shader_it = iterpair.first;
        for (; shader_it != iterpair.second; ++shader_it) {
          shader_it->second->render(this->window);
        }
      }

      glfwSwapBuffers(this->window);
      glfwPollEvents();
    }
  }

  GLContext::~GLContext() {
    debug("destroying GLContext");
    if (window) {
      glfwDestroyWindow(window);
      window = nullptr;
    }
    glfwTerminate();
  }

}