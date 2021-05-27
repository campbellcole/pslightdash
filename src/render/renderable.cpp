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

void Renderable::BASIC_TEXTURED_VAO_REGISTER() {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
  glEnableVertexAttribArray(2);
}

Renderable::Renderable(
    const std::string &name,
    bool basicTexture,
    unsigned int vertexCount,
    float *vertices,
    unsigned int indexCount,
    unsigned int *indices,
    bool dynamicDraw,
    bool generateBuffers,
    VAO_REGISTER_FUNC registerVAO,
    Shader *shader)
    : name(name),
      basicTexture(basicTexture),
      indexCount(indexCount),
      vertexCount(vertexCount),
      generateBuffers(generateBuffers),
      shader(shader) {
  if (!shader)
    this->shader = new Shader(name);

  GLenum usage = GL_STATIC_DRAW;
  if (dynamicDraw)
    usage = GL_DYNAMIC_DRAW;
  else if (!vertices || !indices) {
    log_err("Static EBO requires preset vertex and index data!");
    log_err("Unpredictable behavior will occur.");
  }

  if (generateBuffers) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, usage);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, usage);
  }

  // texture load
  if (basicTexture) {
    texture = new BasicTexture(name + ".png");
  }

  // vertex array load part 2
  registerVAO();
}

Renderable::~Renderable() {
  if (generateBuffers) {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
  }
  if (basicTexture && texture) {
    delete texture;
    texture = nullptr;
  }
  if (shader) { // this will cause a bug where the font shader is deleted and reloaded if text is destroyed, fix later
    delete shader;
    shader = nullptr;
  }
}

void Renderable::setEnabled(bool enabled) {
  this->enabled = enabled;
}

bool Renderable::isEnabled() const {
  return enabled;
}

void Renderable::render(RenderContext *context) {
  if (!enabled) return;
  if (basicTexture) {
    glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
  }
  shader->use();
  shader->setFloatU("uTime", glfwGetTime()); // todo: find a good place to put this
  shader->setFVec2U("uResolution", context->getWidth(), context->getHeight());
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
