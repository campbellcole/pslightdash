#include "render/renderer.hpp"

Renderer::Renderer(RenderContext *context) : context(context) {

}

void Renderer::renderTargets() {
  for (Renderable *r : context->getTargets()) {
    r->render();
  }
}

float lastPress = 0;

void Renderer::handleInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    if (glfwGetTime() - lastPress > 1.0) {
      lastPress = glfwGetTime();
      /*DiscordHooker hooker(
          [redacted]
      );
      hooker.pushToDiscord("sent from WIP c++ code, pretty neat");
       */
    }
  } else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) // temp
  {
    if (glfwGetTime() - lastPress > 1.0) {
      lastPress = glfwGetTime();
      context->getTargets().front()->setEnabled(!context->getTargets().front()->getEnabled());
    }
  }
}

void Renderer::begin() {
  int frameCount = 0;
  double prevTime = 0.0;
  while (!glfwWindowShouldClose(context->window)) {
    double currentTime = glfwGetTime();
    frameCount++;
    if (currentTime - prevTime >= 1.0) {
      std::stringstream ss;
      ss << "DASHRENDER" << " " << PSLIGHTDASH_VERSION << " [" << frameCount << " FPS]";
      glfwSetWindowTitle(context->window, ss.str().c_str());
      frameCount = 0;
      prevTime = currentTime;
    }

    handleInput(context->window);

    renderTargets();

    glfwSwapBuffers(context->window);
    glfwPollEvents();
  }

  glfwTerminate();
}

Renderer::~Renderer() {
  context = nullptr;
}
