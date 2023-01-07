#include "seeder.hpp"

void regions_seeder(const SeederProps &props)
{
  DEBUG("Running regions_seeder...");

  auto collection = props.db["regions"];

  collection.drop();

  cpr::Response r = cpr::Get(cpr::Url{"https://geo.api.gouv.fr/regions"});

  Json::Value root;
  Json::Reader reader;

  if (!reader.parse(r.text, root))
  {
    ERROR("Failed to parse JSON");
    return;
  }

  std::vector<bsoncxx::document::value> documents;
  for (auto &region : root)
  {
    auto document = bsoncxx::builder::stream::document{}
                    << "code" << region["code"].asString()
                    << "name" << region["nom"].asString()
                    << bsoncxx::builder::stream::finalize;
    documents.push_back(document);
  }
  collection.insert_many(documents);
}