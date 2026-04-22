#include "LogAnalyser.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>
#include <vector>
#include <future>
#include <thread>

//---Single File Analysis---
LogStats LogAnalyser::analyse(const std::filesystem::path& filePath) const {
	std::ifstream file(filePath);

	if(!file.is_open()) {
		throw std::runtime_error("Couldn't open file");
	}

	//---Text Log Format---
	//2024-01-01 10:00:00 INFO Start
	static const std::regex textPattern(R"(^(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}) (INFO|WARNING|ERROR) (.*))");

	//---JSON Log Format (flexible spacing)---
	//{"time":"2024-01-01 10:00:01","level":"ERROR","message":"fail"}
	//{ "time":"2024-01-01 10:00:02", "level":"WARNING", "message":"warn" }
	static const std::regex jsonPattern(R"json(\{\s*"time":"(\d{4}-\d{2}-\d{2}\s\d{2}:\d{2}:\d{2})"\s*,\s*"level":"(INFO|WARNING|ERROR)"\s*,\s*"message":"([^"]*)"\s*\})json");

	std::string strLine;
	std::smatch match;
	LogStats stats;

	std::string level;

	while(std::getline(file, strLine)) {
		++stats.lineCount;

		//---Text Format---
		if(std::regex_match(strLine, match, textPattern)) {
			level = match[2];

			if(level == "INFO") ++stats.info;
			else if(level == "WARNING") ++stats.warning;
			else if(level == "ERROR") ++stats.error;
		}
		//---JSON Format---
		else if(std::regex_match(strLine, match, jsonPattern)) {
			level = match[2];

			if(level == "INFO") ++stats.info;
			else if(level == "WARNING") ++stats.warning;
			else if(level == "ERROR") ++stats.error;
		}
		//---Invalid Line---
		else {
			std::cout << "Invalid line: " << strLine << "\n";
		}
	}
	return stats;
}

LogStats LogAnalyser::analyseMultiple(const std::vector<std::filesystem::path>& files) const {

	unsigned int maxThreads = std::thread::hardware_concurrency();
	if(maxThreads == 0) maxThreads = 2;

	std::vector<std::future<LogStats>> futures;
	LogStats total;

	for(size_t i = 0; i < files.size(); i += maxThreads) {

		futures.clear();

		for(size_t j = i; j < i + maxThreads && j < files.size(); ++j) {
		//---Launch async tasks---
			futures.push_back(
				std::async(std::launch::async, [this, &files, j]() {
					return analyse(files[j]);
				})
			);
		}

		//---Collect results---
		for(auto& f : futures) {
			LogStats stats = f.get(); //wait + get result

			total.lineCount += stats.lineCount;
			total.info += stats.info;
			total.warning += stats.warning;
			total.error += stats.error;
		}
	}

	return total;
}

