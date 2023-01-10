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

void insert_bson_to_json(bsoncxx::document::view::const_iterator &it, Json::Value &json, bsoncxx::document::view &doc, const std::string &key)
{
  if (it->type() == bsoncxx::type::k_string)
    json[key] = doc[key].get_string().value.to_string();
  if (it->type() == bsoncxx::type::k_int32)
    json[key] = doc[key].get_int32().value;
  if (it->type() == bsoncxx::type::k_array)
  {
    Json::Value json_array;
    auto array = doc[key].get_array().value;
    for (auto &array_it: array)
      json_array.append(array_it.get_string().value.to_string());
    json[key] = json_array;
  }
}


int strval(const std::string &str)
{
  int result = 0;
  for (auto &c : str)
    result += c;
  return result;
}