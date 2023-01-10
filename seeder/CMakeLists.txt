cmake_minimum_required(VERSION 3.5)
project(autocomplete_api_seeder CXX)

add_executable(${PROJECT_NAME} main.cc)

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon 
# target_link_libraries(${PROJECT_NAME}_test PRIVATE drogon)
#
# and comment out the following lines
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)



find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")

find_package(cpr REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE mongo::mongocxx_shared)
target_link_libraries(${PROJECT_NAME} PRIVATE mongo::bsoncxx_shared)


aux_source_directory(src SRC_DIR)
aux_source_directory(../includes INC_DIR)

target_sources(${PROJECT_NAME} PRIVATE ${SRC_DIR})
target_sources(${PROJECT_NAME} PRIVATE ${INC_DIR})


