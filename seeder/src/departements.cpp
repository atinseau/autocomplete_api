#include "seeder.hpp"

void departements_seeder(const SeederProps &props)
{
  DEBUG("Running departements_seeder...");

  auto departements_collection = props.db["departements"];
  auto regions_collection = props.db["regions"];

  departements_collection.drop();

  mongocxx::cursor regions_cursor = regions_collection.find({});
  for (auto region : regions_cursor)
  {
    // get region code
    std::string region_code = region["code"].get_string().value.to_string();
    cpr::Response r = cpr::Get(cpr::Url{"https://geo.api.gouv.fr/regions/" + region_code + "/departements"});

    Json::Value root;
    Json::Reader reader;

    if (!reader.parse(r.text, root))
    {
      ERROR("Failed to parse JSON");
      return;
    }

    std::vector<bsoncxx::document::value> documents;
    for (auto &departement : root)
    {
      auto document = bsoncxx::builder::stream::document{}
                      << "code" << departement["code"].asString()
                      << "name" << departement["nom"].asString()
                      << "codeRegion" << region_code
                      << bsoncxx::builder::stream::finalize;
      documents.push_back(document);
    }
    departements_collection.insert_many(documents);
  }
}