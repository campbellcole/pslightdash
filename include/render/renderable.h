#ifndef RENDER_RENDERABLE_HPP
#define RENDER_RENDERABLE_HPP

#include <string>
#include <utility>

#include "render/texture.h"
#include "render/shader.h"
#include "render/rendercontext.h"
#include "dbg.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class RenderContext;

class Shader;

class BasicTexture;

typedef void (*VAO_REGISTER_FUNC)(void);

class Renderable {
private:
  Shader *shader = nullptr;
  BasicTexture *texture;
  bool basicTexture, generateBuffers, enabled = true;
protected:
  unsigned int VBO, VAO, EBO, vertexCount, indexCount;
public:
  const std::string name;

  static void DEFAULT_VAO_REGISTER();

  static void COLORED_VAO_REGISTER();

  static void BASIC_TEXTURED_VAO_REGISTER();

  Renderable(const std::string &name,
             bool basicTexture,
             unsigned int vertexCount,
             float *vertices,
             unsigned int indexCount,
             unsigned int *indices,
             bool dynamicDraw = false,
             bool generateBuffers = true,
             VAO_REGISTER_FUNC registerVAO = &Renderable::DEFAULT_VAO_REGISTER,
             Shader *shader = nullptr);

  ~Renderable();

  void setEnabled(bool enabled);

  bool isEnabled() const;

  virtual void render(RenderContext *context);

};


#endif // RENDER_RENDERABLE_HPP
