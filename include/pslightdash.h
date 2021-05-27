#ifndef PSLIGHTDASH_HPP
#define PSLIGHTDASH_HPP

#include <iostream>
#include <sstream>

#include "render/renderer.h" // must be on top because program includes utils which includes windows.h and httplib must be first
#include "render/shader.h"
#include "render/rendercontext.h"
#include "render/text.h"
#include "dbg.h"
#include "pslightdashconfig.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define PSLIGHTDASH_VERSION "" pslightdash_BUILD_TYPE "_v" pslightdash_VERSION_MAJOR "." pslightdash_VERSION_MINOR "." pslightdash_VERSION_PATCH

int main();

#endif // PSLIGHTDASH_HPP
