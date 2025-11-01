#include <gtest/gtest.h>
#include "Tag.h"
#include <algorithm>

using namespace std;

class TagTest : public ::testing::Test {
protected:
    Tag* tag;

    void SetUp() override {
        tag = new Tag("C++", { 1, 2, 3 });
    }

    void TearDown() override {
        delete tag;
    }
};

TEST_F(TagTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(tag->getLabel(), "C++");
    vector<int> expected = { 1, 2, 3 };
    EXPECT_EQ(tag->getPostIds(), expected);
}

TEST_F(TagTest, SetAndGetLabelWorkCorrectly) {
    tag->setLabel("Programming");
    EXPECT_EQ(tag->getLabel(), "Programming");
}

TEST_F(TagTest, SetAndGetPostIdsWorkCorrectly) {
    vector<int> newIds = { 10, 20, 30 };
    tag->setPostIds(newIds);

    const vector<int>& result = tag->getPostIds();
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 20);
    EXPECT_EQ(result[2], 30);
}

TEST_F(TagTest, AddToPostAddsNewId) {
    tag->addToPost(4);
    const vector<int>& ids = tag->getPostIds();

    EXPECT_EQ(ids.size(), 4);
    EXPECT_TRUE(find(ids.begin(), ids.end(), 4) != ids.end());
}

TEST_F(TagTest, AddToPostDoesNotAddDuplicateId) {
    tag->addToPost(2);
    const vector<int>& ids = tag->getPostIds();

    EXPECT_EQ(ids.size(), 3);
    int count = count_if(ids.begin(), ids.end(), [](int id) { return id == 2; });
    EXPECT_EQ(count, 1);
}

TEST_F(TagTest, SetPostIdsClearsOldOnes) {
    vector<int> newIds = { 100, 200 };
    tag->setPostIds(newIds);

    const vector<int>& ids = tag->getPostIds();
    ASSERT_EQ(ids.size(), 2);
    EXPECT_EQ(ids[0], 100);
    EXPECT_EQ(ids[1], 200);
}

TEST_F(TagTest, CombinedOperationsWorkCorrectly) {
    tag->setLabel("Technology");
    tag->addToPost(5);
    tag->addToPost(6);

    EXPECT_EQ(tag->getLabel(), "Technology");

    const vector<int>& ids = tag->getPostIds();
    ASSERT_EQ(ids.size(), 5);
    EXPECT_TRUE(find(ids.begin(), ids.end(), 5) != ids.end());
    EXPECT_TRUE(find(ids.begin(), ids.end(), 6) != ids.end());
}
