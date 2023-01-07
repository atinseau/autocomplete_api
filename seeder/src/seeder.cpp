#include "seeder.hpp"

MongoDbSeeder::MongoDbSeeder()
{
  INFO("MongoDbSeeder::MongoDbSeeder()");
}

const mongocxx::client &MongoDbSeeder::client() const
{
  return (this->_mongodb.client);
}

void MongoDbSeeder::run(void (*seeder)(const SeederProps &))
{
  SeederProps props = {
    this->_mongodb.db,
    this->_mongodb.client
  };
  _futures.push_back(std::async(std::launch::async, seeder, props));
}

void MongoDbSeeder::wait()
{
  for (auto &future : _futures)
    future.wait();
}