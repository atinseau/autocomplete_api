#include <drogon/drogon.h>
#include "includes/app.hpp"

int main() {

    DEBUG("Running on port 8080...");

    drogon::app().addListener("0.0.0.0", 8080);
    drogon::app().run();
    return 0;
}
