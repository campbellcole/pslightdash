//
// Created by campbell on 5/27/2021.
//

#ifndef PSLIGHTDASH_PSLIGHTDASH_H
#define PSLIGHTDASH_PSLIGHTDASH_H

#include <iostream>

#if defined(__APPLE__) && !defined(AUDIOFFT_APPLE_ACCELERATE)
#define AUDIOFFT_APPLE_ACCELERATE
#endif
#include "AudioFFT.h"
#ifndef MINIMP3_IMPLEMENTATION
#define MINIMP3_IMPLEMENTATION
#endif
#include <minimp3/minimp3.h>

#include "dbg.h"
#include "pslightdashconfig.h"
#include "gl/glcontext.h"
#include "renderer.h"
#include "dash/testrendertarget.h"
#include "dash/test3d.h"
#include "dash/text.h"

int main();

#endif //PSLIGHTDASH_PSLIGHTDASH_H
