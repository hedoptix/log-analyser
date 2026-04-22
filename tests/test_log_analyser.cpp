#include <gtest/gtest.h>
#include <fstream>
#include "LogAnalyser.h"

//---Single File---

TEST(LogAnalyserTest, CountsLogLevelsCorrectly) {
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

TEST(LogAnalyserTest, IgnoresInvalidLines) {
	std::ofstream file("test_invalid.log");
	file << "INVALID LINE\n";
	file << "2024-01-01 10:00:00 INFO Valid\n";
	file.close();

	LogAnalyser analyser;
	LogStats stats = analyser.analyse("test_invalid.log");

	EXPECT_EQ(stats.lineCount, 2);
	EXPECT_EQ(stats.info, 1);
	EXPECT_EQ(stats.warning, 0);
	EXPECT_EQ(stats.error, 0);

	std::remove("test_invalid.log");
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

TEST(LogAnalyserTest, MixedFormats) {
	std::ofstream f("mix.log");
	f << "2024-04-04 15:00:00 INFO A\n";
	f << R"json({ "time":"2024-05-20 12:00:00", "level":"ERROR", "message":"fail" })json" << "\n";
	f.close();

	LogAnalyser analyser;
	LogStats stats = analyser.analyseMultiple({"mix.log"});

	EXPECT_EQ(stats.info, 1);
	EXPECT_EQ(stats.error, 1);
}

//---MultiFile---
//---MultiFile correctness---
TEST(LogAnalyserTest, MultiFileAggregation) {
	std::ofstream f1("a.log");
	f1 << "2024-01-01 10:00:00 INFO A\n";
	f1.close();

	std::ofstream f2("b.log");
	f2 << "2024-01-01 10:00:00 ERROR B\n";
	f2.close();

	LogAnalyser analyser;
	LogStats stats = analyser.analyseMultiple({"a.log", "b.log"});

	EXPECT_EQ(stats.lineCount, 2);
	EXPECT_EQ(stats.info, 1);
	EXPECT_EQ(stats.error, 1);
}

//Test race condition---
TEST(LogAnalyserTest, ParallelConsistency) {
	std::ofstream f("test.log");
	for(int i = 0; i < 100; ++i) {
		f << "2024-01-01 10:00:00 INFO A\n";
	}
	f.close();

	LogAnalyser analyser;

	LogStats s1 = analyser.analyseMultiple({"test.log"});
	LogStats s2 = analyser.analyseMultiple({"test.log"});

	EXPECT_EQ(s1.info, s2.info);
}

//---Thread batching---
TEST(LogAnalyserTest, ManyFilesBatching) {
	std::vector<std::filesystem::path> files;

	for(int i = 0; i < 20; ++i) {
		std::string name = "file" + std::to_string(i) + ".log";
		std::ofstream f(name);
		f << "2025-01-01 11:00:00 WARNING X\n";
		f.close();
		files.push_back(name);
	}

	LogAnalyser analyser;
	LogStats stats = analyser.analyseMultiple(files);

	EXPECT_EQ(stats.warning, 20);
}
