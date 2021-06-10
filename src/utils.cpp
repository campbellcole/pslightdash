//
// Created by campbell on 5/25/2021.
//

#include "utils.h"

std::string getResourcePath(const std::string &filename) {
  const int PATH_BUF_SIZE = 1024;
  char pathBuf[PATH_BUF_SIZE];
  uint32_t pathLen = sizeof(pathBuf);
  std::string pathStr;
#ifdef _WIN32
  GetModuleFileNameA(nullptr, pathBuf, PATH_BUF_SIZE);
  pathStr = std::string(pathBuf);
  pathStr = pathStr.substr(0, pathStr.find_last_of('\\')) + "\\res\\" + filename;
#elif defined __APPLE__
  if (_NSGetExecutablePath(pathBuf, &pathLen) == -1)
  {
    log_err("Current path was too long. %d > MAX (%d)", pathLen, PATH_BUF_SIZE);
    exit(1);
  }
  char resolvedPath[PATH_BUF_SIZE];
  realpath(pathBuf, resolvedPath);
  pathStr = std::string(resolvedPath);
  pathStr = pathStr.substr(0, pathStr.find_last_of('/')) + "/res/" + filename;
#endif
  return pathStr;
}