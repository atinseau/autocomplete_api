#include "app.hpp"

mongocxx::instance MongoDb::_instance{};
mongocxx::uri MongoDb::_uri{MONGO_URI};

MongoDb::MongoDb(): client(_uri), db(client[DATABASE_NAME])
{
  INFO("MongoDb::MongoDb()");
}
