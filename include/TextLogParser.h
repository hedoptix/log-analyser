#pragma once

#include "ILogParser.h"
#include <regex>

class TextLogParser : public ILogParser {
public:
	std::optional<LogLevel> parse(const std::string& line) const override;
private:
	//---Text Log Format---
	//2024-01-01 10:00:00 INFO Start
	std::regex pattern{
		R"(^(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}) (INFO|WARNING|ERROR) (.*))"
	};
};
