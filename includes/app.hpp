#ifndef APP_HPP
#define APP_HPP

#define CLEAR "\e[0m"
#define RED "\e[1;31m"
#define YELLOW "\e[1;33m"
#define BLUE "\e[1;36m"
#define PURPLE "\e[1;35m"
#define GREEN "\e[1;32m"

#define LOG(color, output, msg) output << color << msg << CLEAR << std::endl

#define ERROR(msg) LOG(RED, std::cerr, msg)
#define WARNING(msg) LOG(YELLOW, std::cerr, msg)
#define INFO(msg) LOG(BLUE, std::cout, msg)
#define DEBUG(msg) LOG(PURPLE, std::cout, msg)
#define SUCCESS(msg) LOG(GREEN, std::cout, msg)

#define MONGO_URI "mongodb://localhost:27017"

#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#endif