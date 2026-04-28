#include "JsonLogParser.h"

std::optional<LogLevel> JsonLogParser::parse(const std::string& line) const {
	std::smatch match;

	if(std::regex_match(line, match, pattern)) {
		std::string level = match[2];

		if (level == "INFO") return LogLevel::INFO;
	        if (level == "WARNING") return LogLevel::WARNING;
        	if (level == "ERROR") return LogLevel::ERROR;
	}
	return std::nullopt;
}
