#include "ApiController.h"

// Add definition of your processing function here

GeoQuery::GeoQuery(
    ApiController::Req &req,
    const std::string &collection_name,
    const std::string &search_key) : _req(req),
                                     _collection_name(collection_name),
                                     _search_key(search_key)
{
  Json::Value params = getParamsToJSON(req->parameters());

  _search = format_search_string(params["search"].asString());
  _limit = parse_string_to_int(params["limit"].asString());
}

std::vector<Json::Value> GeoQuery::_extract_json(mongocxx::v_noabi::cursor &results, std::initializer_list<std::string> &keys)
{
  std::vector<Json::Value> json_vector;

  for (auto doc : results)
  {
    Json::Value json;
    for (auto key : keys)
      json[key] = doc[key].get_string().value.to_string();
    std::string lower_name = to_lowercase(json[_search_key].asString());

    if (!_search.empty())
    {
      std::string lower_name = to_lowercase(json[_search_key].asString());
      // json["matchScore"] = static_cast<int>(lower_name.find_first_of(REGEX_WHITESPACE));
      json["matchScore"] = static_cast<int>(lower_name.find(_search));
    }

    json_vector.push_back(json);
  }
  std::sort(json_vector.begin(), json_vector.end(), [](const Json::Value &a, const Json::Value &b)
            { return a["matchScore"].asInt() < b["matchScore"].asInt(); });

  return json_vector;
}

std::vector<Json::Value> GeoQuery::find(std::initializer_list<std::string> keys)
{
  auto collection = _mongodb.db.collection(_collection_name);
  mongocxx::options::find opts{};
  if (_limit > 0)
    opts.limit(_limit);
  auto results = collection.find(make_document(
                                     kvp(_search_key, bsoncxx::types::b_regex(string_to_strregex(_search), "i"))),
                                 opts);
  return _extract_json(results, keys);
}

const std::string &GeoQuery::get_search() const
{
  return _search;
}

void ApiController::departements(Req &req, Callback &&callback)
{
  Json::Value json;
  MongoDb mongodb;

  GeoQuery query(req, "departements", "name");

  auto departements = query.find({"code", "name"});

  for (auto &departement : departements)
    json["departements"].append(departement);
  json["count"] = static_cast<int>(departements.size());
  json["type"] = "departements";

  auto resp = HttpResponse::newHttpJsonResponse(json);
  resp->setStatusCode(k200OK);
  callback(resp);
}

void ApiController::regions(Req &req, Callback &&callback)
{
  Json::Value json;
  MongoDb mongodb;

  GeoQuery query(req, "regions", "name");

  auto regions = query.find({"code", "name"});

  for (auto &region : regions)
    json["regions"].append(region);
  json["type"] = "regions";
  json["count"] = static_cast<int>(regions.size());

  auto resp = HttpResponse::newHttpJsonResponse(json);
  resp->setStatusCode(k200OK);
  callback(resp);
}
