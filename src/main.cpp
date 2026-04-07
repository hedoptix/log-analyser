#include <iostream>
#include <filesystem>
#include "LogAnalyser.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
		
	//---Validate input---
	if(argc < 2) {
		std::cerr << "Usage: log_analyser <log_file>\n";
		return 1;
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

		//---Output---
		std::cout << "File: " << filePath << "\n";
		std::cout << "Total lines: " << stats.lineCount << "\n";		
		std::cout << "INFO: " << stats.info << "\n";
		std::cout << "WARNING: " << stats.warning << "\n";
		std::cout << "ERROR: " << stats.error << "\n";	
	}
	catch(const std::exception& e) {
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}

	return 0;
}
