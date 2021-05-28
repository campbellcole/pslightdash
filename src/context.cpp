//
// Created by campbell on 5/27/2021.
//

#include "context.h"

namespace dash {

  Context::Context(unsigned int width, unsigned int height) : width(width), height(height) {}

  void Context::addTarget(Renderable *target) {
    targets.push_back(target);
  }

  void Context::insertTarget(Renderable *target, int position) {
    targets.insert(std::next(targets.begin(), position), target);
  }

  bool Context::removeTarget(const std::string &name) {
    bool found = false;
    bool *fPtr = &found;
    targets.remove_if([name, fPtr](Renderable *t) {
      if (t->getName() == name) {
        *fPtr = true;
        return true;
      } else return false;
    });
    return found;
  }

  std::list<Renderable *> *Context::getTargets() {
    return &targets;
  }

}