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

  auto *test = new dash::impl::TestRenderTarget();
  context->addTarget(test->getInstance());

  renderer->start();

  delete renderer;
  delete context;
  delete test;

  return 0;
}
