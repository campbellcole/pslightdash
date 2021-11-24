//
// Created by campbell on 5/27/2021.
//

#ifndef PSLIGHTDASH_GLCONTEXT_H
#define PSLIGHTDASH_GLCONTEXT_H

#include "pslightdashconfig.h"
#include "gl/glshader.h"
#include "gl/glrendertarget.h"
#include "dbg.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <list>
#include <map>

namespace dash {
  class GLContext {
  private:
    std::map<GLShader *, std::vector<GLRenderTarget *>*> _targetsByShader;
    std::multimap<GLShader *, GLRenderTarget *> targetsByShader;
    typedef std::multimap<GLShader *, GLRenderTarget *>::iterator map_iter;

    unsigned int width, height;

    bool b_initialized = false;

    GLFWwindow *window;

    static void _handleResize(GLFWwindow *window, int width, int height);

    static void _handleMouseMove(GLFWwindow *window, double x, double y);
  public:
    GLContext(unsigned int width, unsigned int height);

    ~GLContext();

    void initialize();

    void addTarget(GLRenderTarget *target);

    bool removeTarget(const std::string &name);

    void start();

    void handleResize(GLFWwindow *window, int width, int height);

    void handleMouseMove(GLFWwindow *window, double x, double y);

    unsigned int getWidth() const;

    unsigned int getHeight() const;

    bool initialized() const;
  };
}


#endif //PSLIGHTDASH_GLCONTEXT_H
