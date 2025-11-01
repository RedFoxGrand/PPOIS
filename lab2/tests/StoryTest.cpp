#include <gtest/gtest.h>
#include "Story.h"
#include "Media.h"

using namespace std;

class StoryTest : public ::testing::Test {
protected:
    Media* media1;
    Media* media2;
    vector<Media>* mediaList;
    Story* story;

    void SetUp() override {
        media1 = new Media(2048, "video1", "https://cdn.example.com/video1.mp4", MediaType::VIDEO, MediaFormat::MP4);
        media2 = new Media(512, "photo1", "https://cdn.example.com/photo1.jpeg", MediaType::PHOTO, MediaFormat::JPEG);
        mediaList = new vector<Media>{ *media1, *media2 };

        story = new Story(
            120,
            "2025-10-24 12:00:00",
            "24h",
            *mediaList
        );
    }

    void TearDown() override {
        delete story;
        delete mediaList;
        delete media2;
        delete media1;
    }
};

TEST_F(StoryTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(story->getViewsCount(), 120);
    EXPECT_EQ(story->getTimestamp(), "2025-10-24 12:00:00");
    EXPECT_EQ(story->getDuration(), "24h");

    auto media = story->getMedia();
    ASSERT_EQ(media.size(), 2);
    EXPECT_EQ(media[0].getName(), "video1");
    EXPECT_EQ(media[1].getName(), "photo1");
}

TEST_F(StoryTest, SettersWorkCorrectly) {
    Media newMedia(1024, "audio1", "https://cdn.example.com/audio1.mp3", MediaType::AUDIO, MediaFormat::MP3);
    story->setViewsCount(300);
    story->setTimestamp("2025-10-25 08:00:00");
    story->setDuration("12h");
    story->setMedia({ newMedia });

    EXPECT_EQ(story->getViewsCount(), 300);
    EXPECT_EQ(story->getTimestamp(), "2025-10-25 08:00:00");
    EXPECT_EQ(story->getDuration(), "12h");

    auto media = story->getMedia();
    ASSERT_EQ(media.size(), 1);
    EXPECT_EQ(media[0].getName(), "audio1");
    EXPECT_EQ(media[0].getUrl(), "https://cdn.example.com/audio1.mp3");
    EXPECT_EQ(media[0].getFormat(), MediaFormat::MP3);
}

TEST_F(StoryTest, IsExpiredReturnsFalseForActiveStory) {
    EXPECT_FALSE(story->isExpired());
}

TEST_F(StoryTest, IsExpiredReturnsTrueWhenDurationIsZero) {
    story->setDuration("0");
    EXPECT_TRUE(story->isExpired());
}

TEST_F(StoryTest, ExpireSetsDurationToZero) {
    story->expire();
    EXPECT_TRUE(story->isExpired());
    EXPECT_EQ(story->getDuration(), "0");
}

TEST_F(StoryTest, ExpireDoesNothingIfAlreadyExpired) {
    story->setDuration("0");
    story->expire();
    EXPECT_EQ(story->getDuration(), "0");
}
