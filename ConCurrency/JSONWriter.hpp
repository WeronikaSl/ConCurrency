#pragma once
#include "json/json.hpp"
#include <fstream>

using json = nlohmann::json;

class JSONWriter
{
public:
	void writeToFile(std::ofstream& o, const std::map<std::string, double>& m) const;
};