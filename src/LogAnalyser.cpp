#include "LogAnalyser.h"
#include "TextLogParser.h"
#include "JsonLogParser.h"

#include <fstream>
#include <stdexcept>
#include <future>
#include <thread>

//---Constructor---
LogAnalyser::LogAnalyser() {
	parsers.push_back(std::make_unique<TextLogParser>());
	parsers.push_back(std::make_unique<JsonLogParser>());
}

//---Single File Analysis---
LogStats LogAnalyser::analyse(const std::filesystem::path& filePath) const {
	std::ifstream file(filePath);

	if(!file.is_open()) {
		throw std::runtime_error("Couldn't open file");
	}

	std::string strLine;
	LogStats stats;

	while(std::getline(file, strLine)) {
		++stats.lineCount;

		//---Try all parsers(Startegy Pattern)---
		for(const auto& parser : parsers) {
			auto level = parser->parse(strLine);

			if(level.has_value()) {
				if(*level == LogLevel::INFO) ++stats.info;
				else if(*level == LogLevel::WARNING) ++stats.warning;
				else if(*level == LogLevel::ERROR) ++stats.error;

				break; //Stop after first successful parser
			}
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

