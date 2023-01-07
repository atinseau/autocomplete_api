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
