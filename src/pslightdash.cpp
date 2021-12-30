#include <iostream>

#include "dbg.h"
#include "pslightdashconfig.h"
#include "gl/glcontext.h"
#include "dash/testrendertarget.h"
#include "dash/test3d.h"
#include "dash/vis/dashvis.h"
#include "dash/text.h"
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

  auto *context = new dash::gl::GLContext(pslightdash_WINDOW_WIDTH, pslightdash_WINDOW_HEIGHT);
  context->initialize();

  auto *testFont = new dash::gl::GLFont("VCR_MONO", 24);
  auto *testText = new dash::impl::Text(testFont, "PSLIGHTDASH", 25, 25, 1, glm::vec3(1, 0, 1));
  context->addTarget(testText->getInstance());

  auto *test = new dash::impl::DashVis(context->getWindow(), testText);
  context->addTarget(test->getInstance());

  context->start();

  delete context;
  delete test;
  delete testFont;
  delete testText;

  return 0;
}
