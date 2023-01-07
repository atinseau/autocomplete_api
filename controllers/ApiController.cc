#include "ApiController.h"

// Add definition of your processing function here

void ApiController::departements(Req &req, Callback &&callback)
{
  Json::Value json;
  MongoDb mongodb;

  DEBUG(mongodb.db.name());

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
