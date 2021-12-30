//
// Created by campbell on 5/27/2021.
//

#include "gl/glcontext.h"

namespace dash::gl {
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

    glfwSetWindowUserPointer(window, this); // bind the window to this context
    glfwSetFramebufferSizeCallback(window, GLContext::_handleResize);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, GLContext::_handleMouseMove);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // uncomment to disable vsync

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
      log_err("Failed to initialize OpenGL");
      glfwTerminate();
      exit(1);
    }

    debug("viewport width: %d\nviewport height: %d", iWidth, iHeight);

    glViewport(0, 0, iWidth, iHeight);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    b_initialized = true;
    log_info("Initialized OpenGL v%s", glGetString(GL_VERSION));
  }

  unsigned int GLContext::getWidth() const {
    return this->width;
  }

  unsigned int GLContext::getHeight() const {
    return this->height;
  }

  GLFWwindow *GLContext::getWindow() const {
    if (this->window == nullptr) {
      log_err("Attempted to get window from uninitialized context. Throwing.");
      throw std::runtime_error("Context not yet initialized");
    }
    return this->window;
  }

  bool GLContext::initialized() const {
    return this->b_initialized;
  }

  void GLContext::addTarget(GLRenderTarget *target) {
    std::vector<GLRenderTarget *> *targets;
    if (_targetsByShader.find(target->getShader()) == _targetsByShader.end()) {
      targets = new std::vector<GLRenderTarget *>();
      _targetsByShader[target->getShader()] = targets;
    } else {
      targets = _targetsByShader[target->getShader()];
    }
    targets->push_back(target);
  }

  bool GLContext::removeTarget(const std::string &name) {
    std::vector<GLRenderTarget *>::iterator it;
    for (auto targets : _targetsByShader) {
      for (it = targets.second->begin(); it < targets.second->end(); it++) {
        if ((*it)->getName() == name) {
          targets.second->erase(it);
          return true;
        }
      }
    }
    return false;
  }

  void GLContext::_handleResize(GLFWwindow *window, int width, int height) {
    ((GLContext *) glfwGetWindowUserPointer(window))->handleResize(window, width, height);
  }

  void GLContext::handleResize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
  }

  void GLContext::_handleMouseMove(GLFWwindow *window, double x, double y) {
    ((GLContext *) glfwGetWindowUserPointer(window))->handleMouseMove(window, x, y);
  }

  void GLContext::handleMouseMove(GLFWwindow *window, double x, double y) {
    for (auto targets : this->_targetsByShader) {
      for (auto target : *targets.second) {
        target->onMouseMove(window, x, y);
      }
    }
  }

  void GLContext::start() {
    int frameCount = 0;
    double prevTime = 0.0;
    double frameDelta = 0.0;
    double deltaAcc = 0.0;
    while (!glfwWindowShouldClose(this->window)) {
      double currentTime = glfwGetTime();
      frameDelta = currentTime - prevTime;
      prevTime = currentTime;
      deltaAcc += frameDelta;
      frameCount++;
      if (deltaAcc >= 1.0) {
        std::stringstream ss;
        ss << "PSLIGHTDASH " << pslightdash_VERSION << " [" << frameCount << " FPS]";
        glfwSetWindowTitle(this->window, ss.str().c_str());
        frameCount = 0;
        deltaAcc = 0.0;
      }

      if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, true);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(0.3, 0.0, 0.8, 1.0);

      for (auto targets : _targetsByShader) {
        targets.first->use();
        GLShader::setDefaultUniforms(targets.first, glm::vec2(this->getWidth(), this->getHeight()));
        if (!targets.second) continue;
        for (auto target : *targets.second) {
          target->checkKeypress(this->window, frameDelta);
          target->render(this->window);
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