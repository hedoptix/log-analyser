#include <iostream>
#include <filesystem>
#include "LogAnalyser.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	//---Validate input---
	if(argc < 2) {
		std::cerr << "Usage: log_analyser <file> [--level LEVEL | --stats]\n";
		return 1;
	}


	fs::path filePath = argv[1];

	//---Check file exists---
	if(!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
		std::cerr << "Error: Invalid file: " << filePath << "\n";
		return 1;
	}

	std::string option = "";
	std::string level = "";

	if(argc >= 3) {
		option = argv[2];
	}

	if(option == "--level" && argc >= 4) {
		level = argv[3];
	}

	try{
		LogAnalyser analyser;
		auto stats = analyser.analyse(filePath);

		if(option == "--stats" || option == "") {
			std::cout << "File: " << filePath << "\n";
			std::cout << "Total lines: " << stats.lineCount << "\n";
			std::cout << "INFO: " << stats.info << "\n";
			std::cout << "WARNING: " << stats.warning << "\n";
			std::cout << "ERROR: " << stats.error << "\n";
		}
		else if(option == "--level") {
			if(level == "INFO") {
				std::cout << "File: " << filePath << "\n";
				std::cout << "Total lines: " << stats.lineCount << "\n";
				std::cout << "INFO: " << stats.info << "\n";
			}
			else if(level == "WARNING") {
				std::cout << "File: " << filePath << "\n";
				std::cout << "Total lines: " << stats.lineCount << "\n";
				std::cout << "WARNING: " << stats.warning << "\n";
			}
			else if(level == "ERROR") {
				std::cout << "File: " << filePath << "\n";
				std::cout << "Total lines: " << stats.lineCount << "\n";
				std::cout << "ERROR: " << stats.error << "\n";
			}
			else {
				std::cerr << "Unknown Option\n";
				return 1;
			}
		}

	}
	catch(const std::exception& e) {
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}

	return 0;
}
