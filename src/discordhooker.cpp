#include "discordhooker.hpp"

DiscordHooker::DiscordHooker(std::string webhookURL, std::string username, std::string avatarURL)
    : webhookURL(webhookURL),
      username(username),
      avatarURL(avatarURL) {
  client = new httplib::SSLClient("discord.com");
}

DiscordHooker::~DiscordHooker() {
  delete client;
  client = nullptr;
}

void DiscordHooker::pushToDiscord(std::string content) {
  Json::Value root;
  root["content"] = content;
  root["username"] = username;
  root["avatar_url"] = avatarURL;
  root["tts"] = false;
  std::stringstream jsonStream;
  jsonStream << root;
  std::string json = jsonStream.str(); // below jsonStream.str() untested, leaving this in case
  auto res = client->Post(webhookURL.c_str(), jsonStream.str(), "application/json");
}

