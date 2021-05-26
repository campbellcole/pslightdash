#ifndef WEBHOOKER_HPP
#define WEBHOOKER_HPP

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "httplib.h"

#include <thread>
#include <string>
#include <sstream>

#include <json/json.h>

#include "dbg.h"

class DiscordHooker {
private:
  const std::string webhookID;
  const std::string webhookToken;
  const std::string username;
public:
  DiscordHooker(const std::string webhookID, const std::string webhookToken, const std::string username);

  ~DiscordHooker();

  void pushToDiscord(const std::string content, const std::string avatarURL = std::string());
};

#endif // WEBHOOKER_HPP
