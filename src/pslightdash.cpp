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

  return 0;
}
