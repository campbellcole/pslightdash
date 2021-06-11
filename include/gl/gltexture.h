//
// Created by campbell on 6/9/2021.
//

#ifndef PSLIGHTDASH_GLTEXTURE_H
#define PSLIGHTDASH_GLTEXTURE_H

#include "stb_image.h"
#include "utils.h"
#include "dbg.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <functional>

namespace dash {

  class GLTexture {
  private:
    unsigned int _textureID;
    static void DEFAULT_TEXTURE_LOAD(unsigned int &textureID, std::string &filename);
  public:
    explicit GLTexture(
        std::string &name,
        std::string filename = "",
        std::function<void(unsigned int&, std::string&)> genTextureFunc = GLTexture::DEFAULT_TEXTURE_LOAD
    );
    unsigned int getTextureID();
  };
}

#endif //PSLIGHTDASH_GLTEXTURE_H
