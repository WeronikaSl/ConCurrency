#include "JSONReader.hpp"

std::map<std::string, double> JSONReader::readFromFile(std::ifstream& ifs) const
{
	json j = json::parse(ifs);
	std::map<std::string, double> temp = j;
	return temp;
}
