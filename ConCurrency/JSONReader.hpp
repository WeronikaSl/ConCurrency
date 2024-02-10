#pragma once
#include "json/json.hpp"
#include <fstream>

using json = nlohmann::json;

class JSONReader
{
public:
	std::map<std::string, double> readFromFile(std::ifstream& ifs) const;
};