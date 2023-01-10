#pragma once

#include <drogon/HttpController.h>
#include "../includes/app.hpp"

using namespace drogon;

class ApiController : public drogon::HttpController<ApiController>
{
public:
  typedef const HttpRequestPtr Req;
  typedef std::function<void(const HttpResponsePtr &)> Callback;

public:
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(ApiController::regions, "/api/v1/regions", Get);
  ADD_METHOD_TO(ApiController::departements, "/api/v1/departements", Get);
  METHOD_LIST_END

  void regions(Req &req, Callback &&callback);
  void departements(Req &req, Callback &&callback);
};


class GeoQuery
{
  public:
    GeoQuery(ApiController::Req &req, const std::string& collection_name, const std::string& search_key);
    std::vector<Json::Value> find(std::initializer_list<std::string> keys);
    const std::string& get_search() const;

  private:
    ApiController::Req& _req;
    std::string _collection_name;
    std::string _search_key;
    MongoDb _mongodb;

    std::string _search;
    int _limit;

    std::vector<Json::Value> _extract_json(mongocxx::v_noabi::cursor& results, std::initializer_list<std::string>& keys);

};
