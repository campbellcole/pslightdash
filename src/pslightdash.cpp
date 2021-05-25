#include "pslightdash.hpp"

int main() {
  const char *pslightdash = "'||''|.   .|'''.|  '||'      '||'  ..|'''.|  '||'  '||' |''||''| '||''|.       |      .|'''.|  '||'  '||' \n"
                            " ||   ||  ||..  '   ||        ||  .|'     '   ||    ||     ||     ||   ||     |||     ||..  '   ||    ||  \n"
                            " ||...|'   ''|||.   ||        ||  ||    ....  ||''''||     ||     ||    ||   |  ||     ''|||.   ||''''||  \n"
                            " ||      .     '||  ||        ||  '|.    ||   ||    ||     ||     ||    ||  .''''|.  .     '||  ||    ||  \n"
                            ".||.     |'....|'  .||.....| .||.  ''|...'|  .||.  .||.   .||.   .||...|'  .|.  .||. |'....|'  .||.  .||. \n" // thanks figlet
                            "Written by pslight (Campbell Cole)\n";
  std::cout << pslightdash;
  std::cout << "Version: " << PSLIGHTDASH_VERSION << std::endl << std::endl;
#ifndef DASHRENDER_DEBUG
  log_info("DEBUG ENABLED");
#endif

  debug("Initializing renderer...");

  RenderContext *context = new RenderContext(WINDOW_WIDTH, WINDOW_HEIGHT);
  Renderer *renderer = new Renderer(context);

  debug("Initialized renderer.");

  float _v1[] = {
      0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
      0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f,
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, -1.0f,
      -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f
  };

  unsigned int _i1[] = {
      0, 1, 3,
      1, 2, 3
  };

  Renderable *testTriangle1 = new Renderable("test", true);
  testTriangle1->setRegisterFunction(&Renderable::TEXTURED_VAO_REGISTER);
  testTriangle1->setRenderInfo(_v1, 32, _i1, 6);
  //context->addTarget(testTriangle1);

  float _v2[] = {
      1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,//   1.0f,  1.0f,
      1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,//   1.0f, -1.0f,
      -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,//  -1.0f, -1.0f,
      -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f//,  -1.0f,  1.0f
  };

  unsigned int _i2[] = {
      0, 1, 3,
      1, 2, 3
  };

  Renderable *background = new Renderable("bg", false);
  background->setRegisterFunction(&Renderable::COLORED_VAO_REGISTER);
  background->setRenderInfo(_v2, 24, _i2, 6);
  context->insertTarget(background, 0);

  debug("Starting render cycle...");
  renderer->begin();

  delete background;
  delete testTriangle1;
  delete renderer;
  delete context;

  return 0;
}
