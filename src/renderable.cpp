//
// Created by campbell on 5/27/2021.
//

#include "renderable.h"

namespace dash {
  Renderable::Renderable(const std::string name) : name(name) {}
  std::string Renderable::getName() const {
    return this->name;
  }
}