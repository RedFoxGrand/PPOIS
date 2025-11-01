#include <gtest/gtest.h>
#include "CacheService.h"
#include <string>
#include <map>

using namespace std;

class CacheServiceTest : public ::testing::Test {
protected:
    CacheService* cache;

    void SetUp() override {
        map<string, string> initialEntries = { {"key1", "value1"}, {"key2", "value2"} };
        cache = new CacheService(3, 60, initialEntries);
    }

    void TearDown() override {
        delete cache;
    }
};

TEST_F(CacheServiceTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(cache->getCacheSize(), 3);
    EXPECT_EQ(cache->getTtlSeconds(), 60);

    auto entries = cache->getEntries();
    EXPECT_EQ(entries.size(), 2);
    EXPECT_EQ(entries.at("key1"), "value1");
    EXPECT_EQ(entries.at("key2"), "value2");
}

TEST_F(CacheServiceTest, SettersWorkCorrectly) {
    map<string, string> newEntries = { {"A", "B"} };

    cache->setCacheSize(10);
    cache->setTtlSeconds(120);
    cache->setEntries(newEntries);

    EXPECT_EQ(cache->getCacheSize(), 10);
    EXPECT_EQ(cache->getTtlSeconds(), 120);
    EXPECT_EQ(cache->getEntries().size(), 1);
    EXPECT_EQ(cache->getEntries().at("A"), "B");
}

TEST_F(CacheServiceTest, PutAddsNewEntry) {
    cache->put("key3", "value3");

    auto entries = cache->getEntries();
    EXPECT_EQ(entries.size(), 3);
    EXPECT_EQ(entries.at("key3"), "value3");
}

TEST_F(CacheServiceTest, PutUpdatesExistingKey) {
    cache->put("key1", "new_value1");

    auto entries = cache->getEntries();
    EXPECT_EQ(entries.size(), 2);
    EXPECT_EQ(entries.at("key1"), "new_value1");
}

TEST_F(CacheServiceTest, PutRemovesOldestEntryWhenFull) {
    cache->put("key3", "value3");
    cache->put("key4", "value4");

    auto entries = cache->getEntries();
    EXPECT_EQ(entries.size(), 3);

    EXPECT_EQ(entries.count("key1"), 0);
    EXPECT_EQ(entries.at("key2"), "value2");
    EXPECT_EQ(entries.at("key3"), "value3");
    EXPECT_EQ(entries.at("key4"), "value4");
}

TEST_F(CacheServiceTest, PutDoesNothingIfKeyEmpty) {
    auto oldEntries = cache->getEntries();
    cache->put("", "someValue");
    EXPECT_EQ(cache->getEntries(), oldEntries);
}

TEST_F(CacheServiceTest, GetReturnsCorrectValue) {
    EXPECT_EQ(cache->get("key1"), "value1");
    EXPECT_EQ(cache->get("key2"), "value2");
}

TEST_F(CacheServiceTest, GetReturnsEmptyStringIfKeyNotFound) {
    EXPECT_EQ(cache->get("unknown"), "");
}

TEST_F(CacheServiceTest, GetReturnsEmptyStringIfKeyEmpty) {
    EXPECT_EQ(cache->get(""), "");
}
