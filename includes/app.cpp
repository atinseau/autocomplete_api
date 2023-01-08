#include "app.hpp"

mongocxx::instance MongoDb::_instance{};
mongocxx::uri MongoDb::_uri{MONGO_URI};

MongoDb::MongoDb() : client(_uri), db(client[DATABASE_NAME])
{
}

Json::Value getParamsToJSON(const std::unordered_map<std::string, std::string, drogon::utils::internal::SafeStringHash> &params)
{
  Json::Value json;
  for (auto &it : params)
    json[it.first] = it.second;
  return json;
}

std::string string_to_strregex(const std::string &str)
{
  std::string formatted = str;
  std::string replaced = REGEX_WHITESPACE;

  int search_index = 0;
  size_t pos;

  if (formatted.length() == 1)
    return formatted;

  while ((pos = formatted.find_first_of(replaced, search_index)) != std::string::npos)
  {
    formatted.replace(pos, 1, replaced);
    search_index = pos + replaced.length();
  }

  return formatted;
}

std::string to_lowercase(const std::string &str)
{
  std::string lower = str;
  std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
  return lower;
}

int parse_string_to_int(const std::string &str)
{
  int result = -1;

  try
  {
    result = std::stoi(str);
  }
  catch (...)
  {
  }
  return result;
}

std::string format_search_string(const std::string &str)
{
  return to_lowercase(str);
}