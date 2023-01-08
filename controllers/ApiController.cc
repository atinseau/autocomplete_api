#include "ApiController.h"

// Add definition of your processing function here

void ApiController::departements(Req &req, Callback &&callback)
{
  Json::Value json;
  MongoDb mongodb;
  int i = 0;

  auto params = getParamsToJSON(req->parameters());
  auto collection = mongodb.db.collection("departements");
  std::string search = params["search"].asString();

  auto departements = collection.find(
      document{} << "name"
                 << open_document
                 << "$regex" << string_to_regex(search)
                 << close_document << finalize);

  json["type"] = "departements";

  std::vector<Json::Value> departements_vector;
  for (auto departement : departements)
  {
    Json::Value json_departement;

    json_departement["code"] = departement["code"].get_string().value.to_string();
    json_departement["name"] = departement["name"].get_string().value.to_string();
    json_departement["codeRegion"] = departement["codeRegion"].get_string().value.to_string();

    std::string lower_name = to_lowercase(json_departement["name"].asString());
    json_departement["matchScore"] = static_cast<int>(lower_name.find(to_lowercase(search)));

    departements_vector.push_back(json_departement);
    i++;
  }
  json["count"] = i;

  std::sort(departements_vector.begin(), departements_vector.end(), [](const Json::Value &a, const Json::Value &b) {
    return a["matchScore"].asInt() < b["matchScore"].asInt();
  });

  for (auto &departement : departements_vector)
    json["departements"].append(departement);

  auto resp = HttpResponse::newHttpJsonResponse(json);
  resp->setStatusCode(k200OK);
  callback(resp);
}

void ApiController::regions(Req &req, Callback &&callback)
{
  Json::Value json;

  json["type"] = "regions";
  for (auto &it : req->parameters())
  {
    json["params"][it.first] = it.second;
  }

  auto resp = HttpResponse::newHttpJsonResponse(json);

  resp->setStatusCode(k200OK);
  callback(resp);
}
