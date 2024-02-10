#include "JSONWriter.hpp"

void JSONWriter::writeToFile(std::ofstream& o, const std::map<std::string, double>& m) const
{
	json j = m;
	o << std::setw(4) << j << std::endl;
}
