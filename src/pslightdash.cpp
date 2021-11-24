#include "pslightdash.h"

int main() {
  const char *pslightdash = "'||''|.   .|'''.|  '||'      '||'  ..|'''.|  '||'  '||' |''||''| '||'''|.      |      .|'''.|  '||'  '||' \n"
                            " ||   ||  ||..  '   ||        ||  .|'     '   ||    ||     ||     ||    ||    |||     ||..  '   ||    ||  \n"
                            " ||...|'   ''|||.   ||        ||  ||    ....  ||''''||     ||     ||    ||   |  ||     ''|||.   ||''''||  \n"
                            " ||      .     '||  ||        ||  '|.    ||   ||    ||     ||     ||    ||  .''''|.  .     '||  ||    ||  \n"
                            ".||.     |'....|'  .||.....| .||.  ''|...'|  .||.  .||.   .||.   .||...|'  .|.  .||. |'....|'  .||.  .||. \n" // thanks figlet
                            "Written by pslight (Campbell Cole)\n";
  std::cout << pslightdash;
  std::cout << "Version: " << pslightdash_VERSION << std::endl << std::endl;
#ifndef DASHRENDER_DEBUG
  log_info("DEBUG ENABLED");
#endif

  auto *context = new dash::GLContext(pslightdash_WINDOW_WIDTH, pslightdash_WINDOW_HEIGHT);

  auto *renderer = new dash::Renderer(context);

  renderer->initialize();

  auto *test = new dash::impl::Test3D();
  auto *testTarget = test->getInstance();
  context->addTarget(testTarget);

  auto *testFont = new dash::GLFont("VCR_MONO", 24);
  auto *testText = new dash::impl::Text(testFont, "PSLIGHTDASH", 25, 25, 1, glm::vec3(1, 1, 1));
  auto *rtarget = testText->build();
  context->addTarget(rtarget);

  renderer->start();

  delete renderer;
  delete context;
  delete test;
  delete testFont;
  delete rtarget;

  return 0;
}
