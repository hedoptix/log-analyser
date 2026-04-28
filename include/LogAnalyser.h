#pragma once 

#include <filesystem>
#include <vector>
#include <memory>

#include "ILogParser.h"

//---Result Struct---
struct LogStats {
	std::size_t lineCount = 0;
	std::size_t info = 0;
	std::size_t warning = 0;
	std::size_t error = 0;
};

//---Main Analyser---
class LogAnalyser {
public:
	LogAnalyser();

	LogStats analyse(const std::filesystem::path& filePath) const;
	LogStats analyseMultiple(const std::vector<std::filesystem::path>& files) const;
private:
	std::vector<std::unique_ptr<ILogParser>> parsers;
};
