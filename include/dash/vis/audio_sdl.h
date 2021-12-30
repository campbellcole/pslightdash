//
// Created by Campbell Cole on 12/28/21.
//

#ifndef PSLIGHTDASH_AUDIO_SDL_H
#define PSLIGHTDASH_AUDIO_SDL_H

#include "decode.h"
#include <SDL2/SDL.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct audio_ctx
{
  int dev;
  SDL_AudioSpec outputSpec;
  decoder *dec;
} audio_ctx;

typedef void (*audio_callback)(audio_ctx *ctx, uint8_t *stream, int len);

void sdl_set_callback(audio_callback callback);
int sdl_audio_init(void **audio_render, int samplerate, int channels, int format, int buffer);
void sdl_audio_release(void *audio_render);
void sdl_audio_set_dec(void *audio_render, decoder *dec);

#ifdef __cplusplus
}
#endif

#endif //PSLIGHTDASH_AUDIO_SDL_H
