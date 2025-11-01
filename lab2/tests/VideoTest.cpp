#include <gtest/gtest.h>
#include "Video.h"

using namespace std;

class VideoTest : public ::testing::Test {
protected:
    Video* video;

    void SetUp() override {
        video = new Video(120, 75, 320, 700, "https://example.com/video.mp4", true, VideoFormat::MP4, { 1920, 1080 });
    }

    void TearDown() override {
        delete video;
    }
};

TEST_F(VideoTest, ConstructorInitializesAllFieldsCorrectly) {
    EXPECT_EQ(video->getDuration(), 120);
    EXPECT_EQ(video->getSoundVolume(), 75);
    EXPECT_EQ(video->getBitrate(), 320);
    EXPECT_EQ(video->getSizeMb(), 700);
    EXPECT_EQ(video->getUrl(), "https://example.com/video.mp4");
    EXPECT_TRUE(video->getHasSubtitles());
    EXPECT_EQ(video->getFormat(), VideoFormat::MP4);

    auto res = video->getResolution();
    EXPECT_EQ(res.first, 1920);
    EXPECT_EQ(res.second, 1080);
}

TEST_F(VideoTest, SettersUpdateValuesCorrectly) {
    video->setDuration(300);
    video->setSoundVolume(50);
    video->setBitrate(512);
    video->setSizeMb(1500);
    video->setUrl("https://example.com/new_video.mov");
    video->setHasSubtitles(false);
    video->setFormat(VideoFormat::MOV);
    video->setResolution({ 1280, 720 });

    EXPECT_EQ(video->getDuration(), 300);
    EXPECT_EQ(video->getSoundVolume(), 50);
    EXPECT_EQ(video->getBitrate(), 512);
    EXPECT_EQ(video->getSizeMb(), 1500);
    EXPECT_EQ(video->getUrl(), "https://example.com/new_video.mov");
    EXPECT_FALSE(video->getHasSubtitles());
    EXPECT_EQ(video->getFormat(), VideoFormat::MOV);

    auto res = video->getResolution();
    EXPECT_EQ(res.first, 1280);
    EXPECT_EQ(res.second, 720);
}

TEST_F(VideoTest, FindoutUrlReturnsCorrectLength) {
    EXPECT_EQ(video->findoutUrl(), static_cast<int>(video->getUrl().length()));

    video->setUrl("abc");
    EXPECT_EQ(video->findoutUrl(), 3);
}

TEST_F(VideoTest, ToggleSubtitlesSwitchesState) {
    EXPECT_TRUE(video->getHasSubtitles());

    video->toggleSubtitles("Some text");
    EXPECT_FALSE(video->getHasSubtitles());

    video->toggleSubtitles("Other text");
    EXPECT_TRUE(video->getHasSubtitles());
}

TEST_F(VideoTest, FormatCanBeChangedToAllEnumValues) {
    video->setFormat(VideoFormat::AVI);
    EXPECT_EQ(video->getFormat(), VideoFormat::AVI);

    video->setFormat(VideoFormat::WMV);
    EXPECT_EQ(video->getFormat(), VideoFormat::WMV);

    video->setFormat(VideoFormat::MPEG);
    EXPECT_EQ(video->getFormat(), VideoFormat::MPEG);
}
