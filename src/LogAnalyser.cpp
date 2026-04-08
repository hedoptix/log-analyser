#include "LogAnalyser.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <regex>

LogStats LogAnalyser::analyse(const std::filesystem::path& filePath) {
	std::ifstream file(filePath);
	if(!file.is_open()) {
		throw std::runtime_error("Couldn't open file");
	}

	std::string strLine;
	LogStats stats;

	//Pattern: YYYY-MM-DD HH:MM:SS LEVEL message
	std::regex logPattern(R"(^(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}) (INFO|WARNING|ERROR) (.*))");
	std::smatch match;
	std::string level;

	while(std::getline(file, strLine)) {
		++stats.lineCount;
		if(std::regex_match(strLine, match, logPattern)) {
			level = match[2];
			if(level == "INFO") ++stats.info;
			else if(level == "WARNING") ++stats.warning;
			else if(level == "ERROR") ++stats.error;
		}
	}
	return stats;
}
