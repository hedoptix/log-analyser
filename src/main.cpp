#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
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


	//---Collect Files---
	std::vector<fs::path> files;
	int index = 1;

	while(index < argc && std::string(argv[index]).rfind("--", 0) != 0) {
		files.push_back(argv[index]);
		++index;
	}

	if(files.empty()) {
		std::cerr << "Error: No input files provided\n";
		return 1;
	}

	//---Validate Files---
	for(const auto& file : files) {
		if(!fs::exists(file)) {
			std::cerr << "Error: File not found: " << file << "\n";
			return 1;
		}
	}

	try{
		LogAnalyser analyser;

		//---Analyse Multiple Files---
		auto stats = analyser.analyseMultiple(files);

		//---Output Handling---
		std::ostream* out = &std::cout;
		std::ofstream fileOut;

		if(index + 1 < argc && std::string(argv[index + 1]) == "--output"){
			fileOut.open(argv[index + 2]);

			if(!fileOut) {
				std::cerr << "Error: Cannot open output file.\n";
				return 1;
			}

			out = &fileOut;
		}

		//---Default | stats---
		if(index >= argc || std::string(argv[index]) == "--stats") {
			*out << "Total lines: " << stats.lineCount << "\n";
			*out << "INFO: " << stats.info << "\n";
			*out << "WARNING: " << stats.warning << "\n";
			*out << "ERROR: " << stats.error << "\n";
		}
		//---Level Filter---
		else if(std::string(argv[index]) == "--level") {
			if(index + 1 >= argc) {
				std::cerr << "Error Missing level\n";
				return 1;
			}

			std::string level = argv[index + 1];

			if(level == "INFO") *out << "INFO: " << stats.info << "\n";
			else if(level == "WARNING") *out << "WARNING: " << stats.warning << "\n";
			else if(level == "ERROR") *out << "Error: " << stats.error << "\n";
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
