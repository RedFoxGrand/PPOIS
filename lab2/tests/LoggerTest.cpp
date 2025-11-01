#include <gtest/gtest.h>
#include "Logger.h"
#include <sstream>

using namespace std;

class LoggerTest : public ::testing::Test {
protected:
    Logger* logger;

    void SetUp() override {
        logger = new Logger("INFO", { "[INFO] System started" });
    }

    void TearDown() override {
        delete logger;
    }
};

TEST_F(LoggerTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(logger->getLogLevel(), "INFO");

    auto logs = logger->getLogs();
    ASSERT_EQ(logs.size(), 1);
    EXPECT_EQ(logs[0], "[INFO] System started");
}

TEST_F(LoggerTest, SettersChangeValuesCorrectly) {
    logger->setLogLevel("DEBUG");
    logger->setLogs({ "[DEBUG] Changed setting" });

    EXPECT_EQ(logger->getLogLevel(), "DEBUG");

    auto logs = logger->getLogs();
    ASSERT_EQ(logs.size(), 1);
    EXPECT_EQ(logs[0], "[DEBUG] Changed setting");
}

TEST_F(LoggerTest, LogAddsMessageAndPrintsIt) {
    stringstream buffer;
    streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

    logger->log("New event logged");

    cout.rdbuf(oldCout);

    auto logs = logger->getLogs();
    ASSERT_EQ(logs.size(), 2);
    EXPECT_EQ(logs.back(), "[INFO] New event logged");

    EXPECT_NE(buffer.str().find("[INFO] New event logged"), string::npos);
}

TEST_F(LoggerTest, LogIgnoresEmptyMessage) {
    auto before = logger->getLogs().size();
    logger->log("");
    auto after = logger->getLogs().size();

    EXPECT_EQ(before, after);
}

TEST_F(LoggerTest, SetLevelChangesLogLevel) {
    logger->setLevel("ERROR");
    EXPECT_EQ(logger->getLogLevel(), "ERROR");

    stringstream buffer;
    streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

    logger->log("Critical failure!");

    cout.rdbuf(oldCout);

    auto logs = logger->getLogs();
    EXPECT_EQ(logs.back(), "[ERROR] Critical failure!");
    EXPECT_NE(buffer.str().find("[ERROR] Critical failure!"), string::npos);
}

TEST_F(LoggerTest, ClearLogsEmptiesLogList) {
    ASSERT_FALSE(logger->getLogs().empty());

    logger->clearLogs();

    EXPECT_TRUE(logger->getLogs().empty());
}

TEST_F(LoggerTest, ClearLogsDoesNothingIfEmpty) {
    logger->clearLogs();
    EXPECT_TRUE(logger->getLogs().empty());

    logger->clearLogs();
    EXPECT_TRUE(logger->getLogs().empty());
}
