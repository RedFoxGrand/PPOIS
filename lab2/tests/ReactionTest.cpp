#include <gtest/gtest.h>
#include "Reaction.h"
#include "Emoji.h"
#include "Like.h"

class ReactionTest : public ::testing::Test {
protected:
    Reaction* reaction;
    Emoji* emoji;
    Like* like;

    void SetUp() override {
        emoji = new Emoji(":smile:", "smile.png");
        like = new Like("2024-01-01 12:00:00", LikeTargetType::POST, true);
        reaction = new Reaction("2024-01-01 12:00:00", *emoji, *like);
    }

    void TearDown() override {
        delete reaction;
        delete like;
        delete emoji;
    }
};

TEST_F(ReactionTest, ConstructorAndGetters) {
    EXPECT_EQ(reaction->getTimestamp(), "2024-01-01 12:00:00");
    EXPECT_EQ(reaction->getEmoji().getCode(), ":smile:");
    EXPECT_EQ(reaction->getEmoji().getImageUrl(), "smile.png");
    EXPECT_EQ(reaction->getLike().getTimestamp(), "2024-01-01 12:00:00");
    EXPECT_EQ(reaction->getLike().getTargetType(), LikeTargetType::POST);
    EXPECT_TRUE(reaction->getLike().getIsLiked());
}

TEST_F(ReactionTest, SetTimestamp) {
    reaction->setTimestamp("2024-01-02 15:30:00");
    EXPECT_EQ(reaction->getTimestamp(), "2024-01-02 15:30:00");
}

TEST_F(ReactionTest, SetEmoji) {
    Emoji newEmoji(":heart:", "heart.png");
    reaction->setEmoji(newEmoji);
    EXPECT_EQ(reaction->getEmoji().getCode(), ":heart:");
    EXPECT_EQ(reaction->getEmoji().getImageUrl(), "heart.png");
}

TEST_F(ReactionTest, SetLike) {
    Like newLike("2024-01-03 10:00:00", LikeTargetType::COMMENT, false);
    reaction->setLike(newLike);
    EXPECT_EQ(reaction->getLike().getTimestamp(), "2024-01-03 10:00:00");
    EXPECT_EQ(reaction->getLike().getTargetType(), LikeTargetType::COMMENT);
    EXPECT_FALSE(reaction->getLike().getIsLiked());
}

TEST_F(ReactionTest, AddReaction) {
    Emoji newEmoji(":fire:", "fire.png");
    Like newLike("2024-01-04 14:00:00", LikeTargetType::POST, true);
    reaction->addReaction(newEmoji, newLike);
    EXPECT_EQ(reaction->getEmoji().getCode(), ":fire:");
    EXPECT_EQ(reaction->getEmoji().getImageUrl(), "fire.png");
    EXPECT_EQ(reaction->getLike().getTimestamp(), "2024-01-04 14:00:00");
    EXPECT_EQ(reaction->getLike().getTargetType(), LikeTargetType::POST);
    EXPECT_TRUE(reaction->getLike().getIsLiked());
}

TEST_F(ReactionTest, DifferentLikeTypes) {
    Like commentLike("2024-01-01 13:00:00", LikeTargetType::COMMENT, true);
    reaction->setLike(commentLike);
    EXPECT_EQ(reaction->getLike().getTargetType(), LikeTargetType::COMMENT);
    EXPECT_TRUE(reaction->getLike().getIsLiked());
}

TEST_F(ReactionTest, DifferentEmojis) {
    Emoji sadEmoji(":sad:", "sad.png");
    reaction->setEmoji(sadEmoji);
    EXPECT_EQ(reaction->getEmoji().getCode(), ":sad:");
    EXPECT_EQ(reaction->getEmoji().getImageUrl(), "sad.png");
}

TEST_F(ReactionTest, MultipleChanges) {
    Emoji emoji1(":star:", "star.png");
    Like like1("2024-01-05 09:00:00", LikeTargetType::COMMENT, false);
    reaction->addReaction(emoji1, like1);
    EXPECT_EQ(reaction->getEmoji().getCode(), ":star:");
    EXPECT_EQ(reaction->getLike().getTargetType(), LikeTargetType::COMMENT);
    EXPECT_FALSE(reaction->getLike().getIsLiked());

    reaction->setTimestamp("2024-01-06 18:00:00");
    EXPECT_EQ(reaction->getTimestamp(), "2024-01-06 18:00:00");

    Emoji emoji2(":rocket:", "rocket.png");
    reaction->setEmoji(emoji2);
    EXPECT_EQ(reaction->getEmoji().getCode(), ":rocket:");
}
