#include "LogAnalyser.h"
#include <fstream>
#include <stdexcept>
#include <string>

LogStats LogAnalyser::analyse(const std::filesystem::path& filePath) {
	std::ifstream file(filePath);
	if(!file.is_open()) {
		throw std::runtime_error("Couldn't open file");
	}

	std::string strLine;
	LogStats stats;

	while(std::getline(file, strLine)) {
		++stats.lineCount;
		if(strLine.rfind("INFO", 0) == 0) ++stats.info;
		else if(strLine.rfind("WARNING", 0) == 0) ++stats.warning;
		else if(strLine.rfind("ERROR", 0) == 0) ++stats.error;
	}
	return stats;
}
