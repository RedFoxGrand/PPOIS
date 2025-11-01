#include <gtest/gtest.h>
#include "Analytics.h"

using namespace std;

class AnalyticsTest : public ::testing::Test {
protected:
    vector<int>* activeUserIds;
    map<string, int>* actionsToday;
    Analytics* analytics;

    void SetUp() override {
        activeUserIds = new vector<int>{ 1, 2, 3, 4, 5 };
        actionsToday = new map<string, int>{
            {"login", 10},
            {"upload", 5}
        };
        analytics = new Analytics(*activeUserIds, *actionsToday);
    }

    void TearDown() override {
        delete analytics;
        delete actionsToday;
        delete activeUserIds;
    }
};

TEST_F(AnalyticsTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(analytics->getActiveUserIds().size(), 5);
    EXPECT_EQ(analytics->getActionsToday().at("login"), 10);
    EXPECT_EQ(analytics->getActionsToday().at("upload"), 5);
}

TEST_F(AnalyticsTest, SettersWorkCorrectly) {
    vector<int> newUsers = { 10, 11 };
    map<string, int> newActions = { {"download", 3}, {"like", 7} };

    analytics->setActiveUserIds(newUsers);
    analytics->setActionsToday(newActions);

    EXPECT_EQ(analytics->getActiveUserIds().size(), 2);
    EXPECT_EQ(analytics->getActionsToday().at("download"), 3);
    EXPECT_EQ(analytics->getActionsToday().at("like"), 7);
}

TEST_F(AnalyticsTest, RecordActionIncrementsCount) {
    analytics->recordAction("login");

    auto actions = analytics->getActions();
    EXPECT_EQ(actions.at("login"), 11);
}

TEST_F(AnalyticsTest, RecordActionAddsNewAction) {
    analytics->recordAction("share");

    auto actions = analytics->getActions();
    EXPECT_EQ(actions.at("share"), 1);
}

TEST_F(AnalyticsTest, RecordActionIgnoresEmptyString) {
    auto before = analytics->getActions().size();
    analytics->recordAction("");
    auto after = analytics->getActions().size();

    EXPECT_EQ(before, after);
}

TEST_F(AnalyticsTest, GetDailyActiveUsersReturnsCorrectValue) {
    EXPECT_EQ(analytics->getDailyActiveUsers(), 5);
}

TEST_F(AnalyticsTest, GetActionsReturnsCopyOfMap) {
    auto actions = analytics->getActions();
    actions["login"] = 999;

    EXPECT_EQ(analytics->getActionsToday().at("login"), 10);
}
