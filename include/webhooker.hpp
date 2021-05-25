#ifndef WEBHOOKER_HPP
#define WEBHOOKER_HPP

#include <string>

#include "httplib.hpp"

class Hooker {
private:
  const std::string &webhookURL;
public:
  Hooker(const std::string &webhookURL);

  void pushToHook(const std::string &content, const std::string &username, const std::string &avatarURL);

  void pushToHook(const char *data);
};

#endif // WEBHOOKER_HPP
