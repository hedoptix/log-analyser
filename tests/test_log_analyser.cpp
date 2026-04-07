#include <gtest/gtest.h>
#include <fstream>
#include "LogAnalyser.h"

TEST(LogAnalyserTest, CountsCorrectly) {
	std::ofstream file("test.log");
	file << "INFO A \n";
	file << "WARNING B\n";
	file << "ERROR C\n";
	file.close();

	LogAnalyser analyser;
	LogStats stats = analyser.analyse("test.log");
	
	EXPECT_EQ(stats.lineCount, 3);
	EXPECT_EQ(stats.info, 1);
	EXPECT_EQ(stats.warning, 1);
	EXPECT_EQ(stats.error, 1);

	std::remove("test.log");
}
