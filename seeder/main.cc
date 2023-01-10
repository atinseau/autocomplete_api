#include "src/seeder.hpp"

int main(int argc, char **argv)
{
  MongoDbSeeder seeder;

  INFO("MongoDbSeeder::run()");

  seeder.run(regions_seeder);
  seeder.wait();
  seeder.run(departements_seeder);
  seeder.wait();
  return (0);
};