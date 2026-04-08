#include <gtest/gtest.h>
#include <fstream>
#include "LogAnalyser.h"

TEST(LogAnalyserTest, CountsCorrectly) {
	std::ofstream file("test.log");
	file << "2024-01-01 10:00:00 INFO A \n";
	file << "2024-01-01 10:00:01 WARNING B\n";
	file << "2024-01-01 10:00:03 ERROR C\n";
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
	file << "2024-02-02 11:00:00 INFO A\n2024-02-02 11:00:03 INFO B\n";
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
	file << "2024-05-01 08:00:00 INFO Start\n";
	file << "2024-05-01 08:00:02 ERROR Fail\n";
	file << "2024-05-01 08:00:04 WARNING Memory\n";
	file << "2024-05-01 08:00:06 INFO Again\n";
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

