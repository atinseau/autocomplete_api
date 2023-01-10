#pragma once

#include "../../includes/app.hpp"

#include <cpr/cpr.h>
#include <unistd.h>

struct SeederProps
{
  const mongocxx::database &db;
  const mongocxx::client &client;
};

class MongoDbSeeder
{
public:
  typedef std::function<void(const SeederProps &)> Seeder;

  MongoDbSeeder();
  const mongocxx::client &client() const;
  void run(Seeder seeder);
  void wait();

private:
  MongoDb _mongodb;
  std::vector<std::future<void>> _futures;
};


void regions_seeder(const SeederProps &props);
void departements_seeder(const SeederProps &props);
void communes_seeder(const SeederProps &props);
