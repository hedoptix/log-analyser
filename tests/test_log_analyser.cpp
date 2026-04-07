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

TEST(LogAnalyserEdgeCases, EmptyFile){
	std::ofstream file("empty.log");
	file.close();

	LogAnalyser analyser;
	LogStats stats = analyser.analyse("empty.log");

	EXPECT_EQ(stats.lineCount, 0);
	EXPECT_EQ(stats.info, 0);
	EXPECT_EQ(stats.warning, 0);
	EXPECT_EQ(stats.error, 0);

	std::remove("empty.log");
}

TEST(LogAnalyserTest, OnlyInfoLogs){
	std::ofstream file("info.log");
	file << "INFO A\nINFO B\n";
	file.close();

	LogAnalyser analyser;
	LogStats stats = analyser.analyse("info.log");

	EXPECT_EQ(stats.lineCount, 2);
	EXPECT_EQ(stats.info, 2);
	EXPECT_EQ(stats.warning, 0);
	EXPECT_EQ(stats.error, 0);

	std::remove("info.log");
}

TEST(LogAnalyserTest, MixedLogs){
	std::ofstream file("mixed.log");
	file << "INFO Start\n";
	file << "ERROR Fail\n";
	file << "WARNING Memory\n";
	file << "INFO Again\n";
	file.close();

	LogAnalyser analyser;
	LogStats stats = analyser.analyse("mixed.log");

	EXPECT_EQ(stats.lineCount, 4);
	EXPECT_EQ(stats.info, 2);
	EXPECT_EQ(stats.warning, 1);
	EXPECT_EQ(stats.error, 1);

	std::remove("mixed.log");
}

TEST(LogAnalyserEdgeCases, InvalidFileThrows) {
	LogAnalyser analyser;
	EXPECT_THROW({
		analyser.analyse("nonexisting.log");
	}, std::runtime_error);
}

