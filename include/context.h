//
// Created by campbell on 5/27/2021.
//

#ifndef PSLIGHTDASH_CONTEXT_H
#define PSLIGHTDASH_CONTEXT_H

#include <string>
#include <list>

#include "renderable.h"

namespace dash {
  class Context {
  private:
    std::list<Renderable *> targets;
    unsigned int width, height;
  public:
    Context(unsigned int width, unsigned int height);
    virtual void initialize() = 0;
    virtual void addTarget(Renderable *target);
    virtual void insertTarget(Renderable *target, int position);
    virtual bool removeTarget(const std::string &name);
    virtual std::list<Renderable *>* getTargets();
  };
}


#endif //PSLIGHTDASH_CONTEXT_H
