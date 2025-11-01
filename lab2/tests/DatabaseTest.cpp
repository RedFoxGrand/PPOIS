#include <gtest/gtest.h>
#include "Database.h"
#include "Exception.h"
#include <sstream>

using namespace std;

class DatabaseTest : public ::testing::Test {
protected:
    Database* db;

    void SetUp() override {
        db = new Database(false, DatabaseType::RELATIONAL, DatabaseConnectionType::LOCAL);
    }

    void TearDown() override {
        delete db;
    }
};

TEST_F(DatabaseTest, ConstructorInitializesCorrectly) {
    EXPECT_FALSE(db->getIsConnected());
    EXPECT_EQ(db->getType(), DatabaseType::RELATIONAL);
    EXPECT_EQ(db->getConnectionType(), DatabaseConnectionType::LOCAL);
}

TEST_F(DatabaseTest, SettersWorkCorrectly) {
    db->setIsConnected(true);
    db->setType(DatabaseType::NON_RELATIONAL);
    db->setConnectionType(DatabaseConnectionType::REMOTE);

    EXPECT_TRUE(db->getIsConnected());
    EXPECT_EQ(db->getType(), DatabaseType::NON_RELATIONAL);
    EXPECT_EQ(db->getConnectionType(), DatabaseConnectionType::REMOTE);
}

TEST_F(DatabaseTest, ConnectSetsIsConnectedToTrue) {
    EXPECT_TRUE(db->connect());
    EXPECT_TRUE(db->getIsConnected());
}

TEST_F(DatabaseTest, ConnectThrowsExceptionIfAlreadyConnected) {
    db->setIsConnected(true);
    EXPECT_THROW(db->connect(), DatabaseConnectionException);
}

TEST_F(DatabaseTest, PrintTypeOutputsCorrectText) {
    std::stringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    db->printType();
    std::cout.rdbuf(oldCout);
    std::string printed = output.str();
    EXPECT_NE(printed.find("реляционная"), std::string::npos);
}

TEST_F(DatabaseTest, PrintTypeOutputsNonRelationalText) {
    db->setType(DatabaseType::NON_RELATIONAL);

    std::stringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    db->printType();
    std::cout.rdbuf(oldCout);

    std::string printed = output.str();
    EXPECT_NE(printed.find("нереляционная"), std::string::npos);
}
