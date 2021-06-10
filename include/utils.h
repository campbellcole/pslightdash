//
// Created by campbell on 5/25/2021.
//

#ifndef PSLIGHTDASH_UTILS_H
#define PSLIGHTDASH_UTILS_H

#ifdef _WIN32

#include <Windows.h>
#include <libloaderapi.h>

#elif defined __APPLE__
#include <mach-o/dyld.h>
#include <unistd.h>
#include <cstdlib>
#endif

#include <string>

std::string getResourcePath(const std::string &filename);

#endif //PSLIGHTDASH_UTILS_H
