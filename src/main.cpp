#include <iostream>
#include <filesystem>
#include <fstream>
#include "LogAnalyser.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	//---Validate input---
	if(argc < 2 || std::string(argv[1]) == "--help") {
		std::cout << "Usage:\n";
		std::cout << "log_analyser <log_file>\n";
		std::cout << "log_analyser <log_file> --stats\n";
		std::cout << "log_analyser <log_file> --level INFO|WARNING|ERROR\n";
		std::cout << "log_analyser <log_file> --stats --output <file>\n";
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

		//---Output Handling---
		std::ostream* out = &std::cout;
		std::ofstream fileOut;
		
		if(argc >= 5 && std::string(argv[3]) == "--output"){
			fileOut.open(argv[4]);
			
			if(!fileOut) {
				std::cerr << "Error: Cannot open output file.\n";
				return 1;
			}

			out = &fileOut;
		}

		//---Default | stats---
		if(argc == 2 || std::string(argv[2]) == "--stats") {
			*out << "File: " << filePath << "\n";
			*out << "Total lines: " << stats.lineCount << "\n";
			*out << "INFO: " << stats.info << "\n";
			*out << "WARNING: " << stats.warning << "\n";
			*out << "ERROR: " << stats.error << "\n";
		}
		//---Level Filter---
		else if(std::string(argv[2]) == "--level" && argc == 4) {
			std::string level = argv[3];

			if(level == "INFO") *out << stats.info << "\n";
			else if(level == "WARNING") *out << stats.warning << "\n";
			else if(level == "ERROR") *out << stats.error << "\n";
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
