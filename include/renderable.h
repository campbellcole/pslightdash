//
// Created by campbell on 5/27/2021.
//

#ifndef PSLIGHTDASH_RENDERABLE_H
#define PSLIGHTDASH_RENDERABLE_H

#include <string>
namespace dash {
  class Renderable {
  private:
    std::string name;
  public:
    Renderable(std::string name);
    std::string getName() const;
  };
}

#endif //PSLIGHTDASH_RENDERABLE_H
