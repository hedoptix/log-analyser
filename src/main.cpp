#include <iostream>
#include <filesystem>
#include "LogAnalyser.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	//---Validate input---
	if(argc < 2 || std::string(argv[1]) == "--help") {
		std::cout << "Usage:\n";
		std::cout << "log_analyser <log_file>\n";
		std::cout << "log_analyser <log_file> --stats\n";
		std::cout << "log_analyser <log_file> --level INFO|WARNING|ERROR\n";
		return 0;
	}


	fs::path filePath = argv[1];

	//---Check file exists---
	if(!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
		std::cerr << "Error: Invalid file: " << filePath << "\n";
		return 1;
	}

	try{
		LogAnalyser analyser;
		auto stats = analyser.analyse(filePath);

		if(argc == 2 || std::string(argv[2]) == "--stats") {
			std::cout << "File: " << filePath << "\n";
			std::cout << "Total lines: " << stats.lineCount << "\n";
			std::cout << "INFO: " << stats.info << "\n";
			std::cout << "WARNING: " << stats.warning << "\n";
			std::cout << "ERROR: " << stats.error << "\n";
		}
		else if(std::string(argv[2]) == "--level" && argc == 4) {
			std::string level = argv[3];

			if(level == "INFO") std::cout << stats.info << "\n";
			else if(level == "WARNING") std::cout << stats.warning << "\n";
			else if(level == "ERROR") std::cout << stats.error << "\n";
			else {
				std::cerr << "Invalid level\n";
				return 1;
			}
		}
		else {
			std::cerr << "Invalid argument. Use --help\n";
			return 1;
		}

	}
	catch(const std::exception& e) {
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}

	return 0;
}
