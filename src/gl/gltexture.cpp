//
// Created by campbell on 6/9/2021.
//

#include "gl/gltexture.h"

namespace dash {
  void GLTexture::DEFAULT_TEXTURE_LOAD(unsigned int &textureID, std::string &filename) {
    debug("Loading texture: %s", filename.c_str());
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    std::string resPath = getResourcePath("img/" + filename);

    int width, height, nChannels;
    unsigned char *data = stbi_load(resPath.c_str(), &width, &height, &nChannels, 0);
    if (data) {
      GLenum imgFmt;
      switch (nChannels) {
        case 1:
          imgFmt = GL_RED;
          break;
        case 2:
          imgFmt = GL_RG;
          break;
        case 3:
          imgFmt = GL_RGB;
          break;
        case 4:
          imgFmt = GL_RGBA;
          break;
        default:
          imgFmt = GL_RGB;
          break;
      }
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, imgFmt, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    } else {
      log_err("Failed to load texture: %s", filename.c_str());
    }
    stbi_image_free(data);
  }

  GLTexture::GLTexture(std::string &name, std::string filename, std::function<void(unsigned int &, std::string &)> genTextureFunc) {
    if (filename.empty())
      filename = name + ".png";
    genTextureFunc(this->_textureID, filename);
  }

  unsigned int GLTexture::getTextureID() {
    return this->_textureID;
  }

}