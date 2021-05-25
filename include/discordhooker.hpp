#ifndef WEBHOOKER_HPP
#define WEBHOOKER_HPP

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "httplib.hpp"

#include <string>
#include <sstream>

#include <json/json.h>

#include "dbg.h"

class DiscordHooker {
private:
  std::string webhookURL;
  std::string username;
  std::string avatarURL;
  httplib::SSLClient *client;
public:
  DiscordHooker(std::string webhookURL, std::string username, std::string avatarURL);

  ~DiscordHooker();

  void pushToDiscord(std::string content);
};

#endif // WEBHOOKER_HPP
