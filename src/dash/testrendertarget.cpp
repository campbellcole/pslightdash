//
// Created by campbell on 6/9/2021.
//

#include "dash/testrendertarget.h"

namespace dash::impl {
  GLRenderTarget *TestRenderTarget::build() {
    float vertices[] {
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,//   1.0f,  1.0f,
        1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,//   1.0f, - 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,//  -1.0f, -1.0f,
        -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f//,  -1.0f,  1.0f
    };
    unsigned int indices[] {
        0, 1, 3,
        1, 2, 3
    };
    unsigned int vertexCount = 24, indexCount = 6;
    auto *targetBuilder = new GLRenderTargetBuilder();
    targetBuilder->withName("bg")->withVAORegisterFunction([] {
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
      glEnableVertexAttribArray(1);
    })->withRenderData(vertices, indices, vertexCount, indexCount)->withRenderFunction([indexCount](GLRenderTarget *target) {
      glBindVertexArray(target->getVAO());
      glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    });
    auto built = targetBuilder->build();
    delete targetBuilder;
    return built;
  }
}