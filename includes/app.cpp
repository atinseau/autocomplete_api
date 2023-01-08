#include "app.hpp"

mongocxx::instance MongoDb::_instance{};
mongocxx::uri MongoDb::_uri{MONGO_URI};

MongoDb::MongoDb(): client(_uri), db(client[DATABASE_NAME])
{}

Json::Value getParamsToJSON(const std::unordered_map<std::string, std::string, drogon::utils::internal::SafeStringHash> &params)
{
  Json::Value json;
  for (auto &it : params)
    json[it.first] = it.second;
  return json;
}

bsoncxx::types::b_regex string_to_regex(const std::string& str)
{
  return bsoncxx::types::b_regex{str, "i"};
}

std::string to_lowercase(const std::string& str)
{
  std::string lower = str;
  std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
  return lower;
}