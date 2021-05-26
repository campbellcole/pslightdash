#ifndef RENDER_RENDERABLE_HPP
#define RENDER_RENDERABLE_HPP

#include <string>

#include "render/texture.h"
#include "render/program.h"
#include "render/rendercontext.h"
#include "dbg.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef void (*VAO_REGISTER_FUNC)(void);

class RenderContext;

class Program;

class Texture;

class Renderable {
private:
  RenderContext *parentContext = nullptr;
  Program *program = nullptr;
  Texture *texture;
  bool textured, enabled = true;
  float *vertices;
  unsigned int *indices;
  unsigned int VBO, VAO, EBO, vertexCount, indexCount;
  VAO_REGISTER_FUNC registerVAO;
public:
  const std::string name;

  static void DEFAULT_VAO_REGISTER();

  static void COLORED_VAO_REGISTER();

  static void TEXTURED_VAO_REGISTER();

  Renderable(const std::string &name, bool textured);

  ~Renderable();

  void setEnabled(bool enabled);

  bool getEnabled();

  void setRegisterFunction(VAO_REGISTER_FUNC registerVAO);

  void setRenderInfo(float *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount);

  void initialize(RenderContext *context);

  void render();
};


#endif // RENDER_RENDERABLE_HPP
