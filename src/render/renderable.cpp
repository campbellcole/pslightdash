#include "render/renderable.h"

void Renderable::DEFAULT_VAO_REGISTER() {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
  glEnableVertexAttribArray(0);
}

void Renderable::COLORED_VAO_REGISTER() {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void Renderable::TEXTURED_VAO_REGISTER() {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
  glEnableVertexAttribArray(2);
}

Renderable::Renderable(const std::string &name, bool textured) : name(name), textured(textured) {}

Renderable::~Renderable() {
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);
  if (textured && texture) {
    delete texture;
    texture = nullptr;
  }
  if (program) {
    delete program;
    program = nullptr;
  }
}

void Renderable::setEnabled(bool enabled) {
  this->enabled = enabled;
}

bool Renderable::getEnabled() {
  return enabled;
}

void Renderable::setRegisterFunction(VAO_REGISTER_FUNC registerVAO) {
  this->registerVAO = registerVAO;
}

void
Renderable::setRenderInfo(float *vertices, unsigned int vertexCount, unsigned int *indices, unsigned int indexCount) {
  this->vertices = vertices;
  this->vertexCount = vertexCount;
  this->indices = indices;
  this->indexCount = indexCount;
}

void Renderable::initialize(RenderContext *context) {
  parentContext = context;
  program = new Program(name);

  // vertex array load part 1
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // vertex buffer load
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

  // element array load
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

  // texture load
  if (textured) {
    texture = new Texture(name + ".png");
  }

  // vertex array load part 2
  registerVAO();
}

void Renderable::render() {
  if (!enabled) return;
  if (textured) {
    glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
  }
  program->use();
  program->setFloatU("uTime", glfwGetTime()); // todo: find a good place to put this
  program->setFVec2U("uResolution", parentContext->getWidth(), parentContext->getHeight());
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}
