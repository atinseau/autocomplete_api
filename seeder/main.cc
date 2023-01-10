#include "src/seeder.hpp"

int main(int argc, char **argv)
{
  MongoDbSeeder mongoDbSeeder;
  std::map<std::string, MongoDbSeeder::Seeder> seeders = {
      {"regions", regions_seeder},
      {"departements", departements_seeder},
      {"communes", communes_seeder}};

  INFO("MongoDbSeeder::run()");

  if (argc > 1)
  {
    for (int i = 1; i < argc; ++i)
    {
      std::string seederName = argv[i];
      if (seeders.find(seederName) != seeders.end())
      {
        mongoDbSeeder.run(seeders[seederName]);
        mongoDbSeeder.wait();
      }
      else
      {
        ERROR("Seeder not found: " << seederName);
      }
    }
    return (0);
  }

  for (auto it = seeders.rbegin(); it != seeders.rend(); ++it)
  {
    mongoDbSeeder.run(it->second);
    mongoDbSeeder.wait();
  }

  return (0);
};