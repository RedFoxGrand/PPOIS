#include <gtest/gtest.h>
#include "SearchEngine.h"
#include <regex>
#include <thread>
#include <chrono>

using namespace std;

class SearchEngineTest : public ::testing::Test {
protected:
    SearchEngine* engine;

    void SetUp() override {
        engine = new SearchEngine(5, "01.01.2025 00:00:00", "the,and,or", "tf-idf",
            { "apple", "banana", "application", "orange", "pineapple" });
    }

    void TearDown() override {
        delete engine;
    }
};

TEST_F(SearchEngineTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(engine->getIndexSize(), 5);
    EXPECT_EQ(engine->getLastUpdate(), "01.01.2025 00:00:00");
    EXPECT_EQ(engine->getStopWords(), "the,and,or");
    EXPECT_EQ(engine->getRankingAlgorithm(), "tf-idf");

    auto terms = engine->getIndexedTerms();
    ASSERT_EQ(terms.size(), 5);
    EXPECT_EQ(terms[0], "apple");
    EXPECT_EQ(terms[4], "pineapple");
}

TEST_F(SearchEngineTest, SettersUpdateValuesCorrectly) {
    engine->setIndexSize(10);
    engine->setLastUpdate("24.10.2025 12:00:00");
    engine->setStopWords("a,an,the");
    engine->setRankingAlgorithm("BM25");
    engine->setIndexedTerms({ "dog", "cat" });

    EXPECT_EQ(engine->getIndexSize(), 10);
    EXPECT_EQ(engine->getLastUpdate(), "24.10.2025 12:00:00");
    EXPECT_EQ(engine->getStopWords(), "a,an,the");
    EXPECT_EQ(engine->getRankingAlgorithm(), "BM25");

    auto terms = engine->getIndexedTerms();
    ASSERT_EQ(terms.size(), 2);
    EXPECT_EQ(terms[0], "dog");
    EXPECT_EQ(terms[1], "cat");
}

TEST_F(SearchEngineTest, SearchReturnsMatchingTerms) {
    auto results = engine->search("apple");

    ASSERT_EQ(results.size(), 2);
    EXPECT_EQ(results[0], "apple");
    EXPECT_EQ(results[1], "pineapple");
}

TEST_F(SearchEngineTest, SearchReturnsEmptyForEmptyQuery) {
    auto results = engine->search("");
    EXPECT_TRUE(results.empty());
}

TEST_F(SearchEngineTest, SearchReturnsEmptyIfNoMatch) {
    auto results = engine->search("carrot");
    EXPECT_TRUE(results.empty());
}

TEST_F(SearchEngineTest, ReindexClearsAndUpdatesLastUpdate) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    engine->reindex();

    auto terms = engine->getIndexedTerms();
    EXPECT_TRUE(terms.empty());

    string newDate = engine->getLastUpdate();
    regex datePattern(R"(\d{2}\.\d{2}\.\d{4} \d{2}:\d{2}:\d{2})");
    EXPECT_TRUE(regex_match(newDate, datePattern));
}
