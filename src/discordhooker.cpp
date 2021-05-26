#include "discordhooker.h"

DiscordHooker::DiscordHooker(const std::string webhookID, const std::string webhookToken, const std::string username)
    : webhookID(webhookID),
      webhookToken(webhookToken),
      username(username) {}

DiscordHooker::~DiscordHooker() = default;

void DiscordHooker::pushToDiscord(const std::string content, const std::string avatarURL) {
  debug("Generating JSON and webhook URL...");
  Json::Value root;
  root["content"] = content;
  root["username"] = username;
  if (!avatarURL.empty())
    root["avatar_url"] = avatarURL;
  root["tts"] = false;
  std::stringstream jsonStream;
  jsonStream << root;
  std::string json = jsonStream.str();
  std::string url = "/api/webhooks/";
  url += webhookID + "/" + webhookToken;
  debug("Sending POST request in new thread...");
  std::thread req([url, json] {
    httplib::SSLClient client("discord.com");
    auto req = client.Post(url.c_str(), json, "application/json");
  });
  req.detach();
}

