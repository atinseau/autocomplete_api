#include "../includes/app.hpp"

int main()
{
  std::cout << "Running migrations..." << std::endl;

  mongocxx::instance instance{};
  mongocxx::uri uri{MONGO_URI};
  mongocxx::client client{uri};

  mongocxx::database db = client["test"];

  std::cout << db.name() << std::endl;

  auto collection = db.collection("users");

  std::cout << collection.count_documents({}) << std::endl;

  return (0);
};