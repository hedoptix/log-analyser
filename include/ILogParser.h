#pragma once

#include <optional>
#include <string>

enum class LogLevel {
	INFO,
	WARNING,
	ERROR
};

class ILogParser {
public:
	virtual ~ILogParser() noexcept = default;

	virtual std::optional<LogLevel> parse(const std::string& line) const = 0;
};
