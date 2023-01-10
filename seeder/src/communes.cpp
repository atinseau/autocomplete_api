#include "seeder.hpp"

void communes_seeder(const SeederProps &props)
{
  DEBUG("Running communes_seeder...");

  auto communes_collection = props.db["communes"];
  auto departements_collection = props.db["departements"];

  communes_collection.drop();

  mongocxx::cursor departements_cursor = departements_collection.find({});
  for (auto departements : departements_cursor)
  {
    auto name = departements["name"].get_string().value.to_string();
    auto code = departements["code"].get_string().value.to_string();

    cpr::Response r = cpr::Get(cpr::Url{"https://geo.api.gouv.fr/departements/" + code + "/communes"});

    Json::Value root;
    Json::Reader reader;

    if (!reader.parse(r.text, root))
    {
      ERROR("Failed to parse JSON");
      return;
    }

    std::vector<bsoncxx::document::value> documents;
    for (auto &commune : root)
    {

      auto postal_codes = commune["codesPostaux"];
      auto postal_codes_array = bsoncxx::builder::basic::array{};

      for (const auto &postal_code : postal_codes)
        postal_codes_array.append(postal_code.asString());

      auto document = bsoncxx::builder::stream::document{}
                      << "code" << commune["code"].asString()
                      << "codeDepartement" << commune["codeDepartement"].asString()
                      << "codeEpci" << commune["codeEpci"].asString()
                      << "codeRegion" << commune["codeRegion"].asString()
                      << "name" << commune["nom"].asString()
                      << "population" << commune["population"].asInt()
                      << "siren" << commune["siren"].asString()
                      << "postalCodes" << postal_codes_array
                      << bsoncxx::builder::stream::finalize;
      documents.push_back(document);
    }
    communes_collection.insert_many(documents);
  }
}