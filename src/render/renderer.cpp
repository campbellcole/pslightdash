#include "render/renderer.h"

Renderer::Renderer(int width, int height) {
  context = new RenderContext(width, height);
}

void Renderer::renderTargets() {
  for (Renderable *r : context->getTargets()) {
    r->render();
  }
}

RenderContext* Renderer::getContext() {
  return context;
}

float lastPress = 0;

void Renderer::handleInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    if (glfwGetTime() - lastPress > 1.0) {
      lastPress = glfwGetTime();
      DiscordHooker hooker(
          "846954096429760552",
          "ZZvE6UH1fuTQsQESuVIketdx56zS9WzUg2yCbeb8xyV8JVwjULfCKrhMv-YK0ADrzrWo",
          "test"
      );
      hooker.pushToDiscord("pslightdash font update", "https://cdn.discordapp.com/avatars/165294621855973376/e2bfbea998af88049bbe7cc5eda5d50b.png");
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
  Font test("VCR_MONO", 24);
  while (!glfwWindowShouldClose(context->window)) {
    double currentTime = glfwGetTime();
    frameCount++;
    if (currentTime - prevTime >= 1.0) {
      std::stringstream ss;
      ss << "PSLIGHTDASH " << PSLIGHTDASH_VERSION << " [" << frameCount << " FPS]";
      glfwSetWindowTitle(context->window, ss.str().c_str());
      frameCount = 0;
      prevTime = currentTime;
    }

    handleInput(context->window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderTargets();

    test.draw("PSLIGHTDASH", 15, 15, 1, glm::ivec3(0.7, 0.0, 0.3));

    glfwSwapBuffers(context->window);
    glfwPollEvents();
  }

  glfwTerminate();
}

Renderer::~Renderer() {
  delete context;
  context = nullptr;
}

