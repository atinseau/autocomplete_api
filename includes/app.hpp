#ifndef APP_HPP
#define APP_HPP

#define CLEAR "\e[0m"
#define RED "\e[1;31m"
#define YELLOW "\e[1;33m"
#define BLUE "\e[1;36m"
#define PURPLE "\e[1;35m"
#define GREEN "\e[1;32m"

#define REGEX_WHITESPACE "[ -]"

#define LOG(color, output, msg) output << color << msg << CLEAR << std::endl

#define ERROR(msg) LOG(RED, std::cerr, msg)
#define WARNING(msg) LOG(YELLOW, std::cerr, msg)
#define INFO(msg) LOG(BLUE, std::cout, msg)
#define DEBUG(msg) LOG(PURPLE, std::cout, msg)
#define SUCCESS(msg) LOG(GREEN, std::cout, msg)

#define MONGO_URI "mongodb://localhost:27017"
#define DATABASE_NAME "autocomplete_api"

#include <iostream>

#include <drogon/drogon.h>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::close_document;

class MongoDb
{
private:
  static mongocxx::instance _instance;
  static mongocxx::uri _uri;

public:
  MongoDb();

  mongocxx::client client;
  mongocxx::database db;
};

// UTIlS
Json::Value getParamsToJSON(const std::unordered_map<std::string, std::string, drogon::utils::internal::SafeStringHash> &params);
std::string string_to_strregex(const std::string& str);
std::string to_lowercase(const std::string& str);

int parse_string_to_int(const std::string& str);
std::string format_search_string(const std::string& str);

void insert_bson_to_json(bsoncxx::document::view::const_iterator &it, Json::Value &json, bsoncxx::document::view &doc, const std::string &key);

int strval(const std::string &str);

#endif
