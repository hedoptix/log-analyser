#pragma once

#include "ILogParser.h"
#include <regex>

class JsonLogParser : public ILogParser {
public:
	std::optional<LogLevel> parse(const std::string& line) const override;
private:
	//---JSON Log Format (flexible spacing)---
	//{"time":"2024-01-01 10:00:01","level":"ERROR","message":"fail"}
	//{ "time":"2024-01-01 10:00:02", "level":"WARNING", "message":"warn" }
	std::regex pattern{
		R"json(\{\s*"time":"(\d{4}-\d{2}-\d{2}\s\d{2}:\d{2}:\d{2})"\s*,\s*"level":"(INFO|WARNING|ERROR)"\s*,\s*"message":"([^"]*)"\s*\})json"
	};
};
