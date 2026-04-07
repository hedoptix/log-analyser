#pragma once
#include <filesystem>

struct LogStats {
	std::size_t lineCount = 0;
	std::size_t info = 0;
	std::size_t warning = 0;
	std::size_t error = 0;
};

class LogAnalyser {
public:
	LogStats analyse(const std::filesystem::path& filePath);

};
