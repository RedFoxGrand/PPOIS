#include <gtest/gtest.h>
#include "Media.h"
using namespace std;

class MediaTest : public ::testing::Test {
protected:
    Media* media;

    void SetUp() override {
        media = new Media(2048, "VideoFile", "http://example.com/video.mp4", MediaType::VIDEO, MediaFormat::MP4);
    }

    void TearDown() override {
        delete media;
    }
};

TEST_F(MediaTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(media->getSizeKb(), 2048);
    EXPECT_EQ(media->getName(), "VideoFile");
    EXPECT_EQ(media->getUrl(), "http://example.com/video.mp4");
    EXPECT_EQ(media->getType(), MediaType::VIDEO);
    EXPECT_EQ(media->getFormat(), MediaFormat::MP4);
}

TEST_F(MediaTest, SettersAndGettersWorkCorrectly) {
    media->setSizeKb(512);
    media->setName("Photo");
    media->setUrl("http://example.com/photo.jpg");
    media->setType(MediaType::PHOTO);
    media->setFormat(MediaFormat::JPEG);

    EXPECT_EQ(media->getSizeKb(), 512);
    EXPECT_EQ(media->getName(), "Photo");
    EXPECT_EQ(media->getUrl(), "http://example.com/photo.jpg");
    EXPECT_EQ(media->getType(), MediaType::PHOTO);
    EXPECT_EQ(media->getFormat(), MediaFormat::JPEG);
}

TEST_F(MediaTest, ValidateFormatReturnsTrueForCorrectCombinations) {
    EXPECT_TRUE(media->validateFormat());
    media->setType(MediaType::PHOTO); media->setFormat(MediaFormat::JPEG); EXPECT_TRUE(media->validateFormat());
    media->setType(MediaType::TEXT); media->setFormat(MediaFormat::TXT); EXPECT_TRUE(media->validateFormat());
    media->setType(MediaType::AUDIO); media->setFormat(MediaFormat::MP3); EXPECT_TRUE(media->validateFormat());
    media->setType(MediaType::DOCUMENT); media->setFormat(MediaFormat::PDF); EXPECT_TRUE(media->validateFormat());
}

TEST_F(MediaTest, ValidateFormatReturnsFalseForIncorrectCombinations) {
    media->setType(MediaType::PHOTO); media->setFormat(MediaFormat::MP4); EXPECT_FALSE(media->validateFormat());
    media->setType(MediaType::TEXT); media->setFormat(MediaFormat::JPEG); EXPECT_FALSE(media->validateFormat());
    media->setType(MediaType::VIDEO); media->setFormat(MediaFormat::MP3); EXPECT_FALSE(media->validateFormat());
}

TEST_F(MediaTest, CompressMediaReducesSizeForVideo) {
    int originalSize = media->getSizeKb();
    media->compressMedia();
    EXPECT_LT(media->getSizeKb(), originalSize);
    EXPECT_EQ(media->getSizeKb(), originalSize * 60 / 100);
}

TEST_F(MediaTest, CompressMediaReducesSizeForPhoto) {
    media->setType(MediaType::PHOTO); media->setFormat(MediaFormat::JPEG); media->setSizeKb(3000);
    media->compressMedia();
    EXPECT_EQ(media->getSizeKb(), 3000 * 70 / 100);
}

TEST_F(MediaTest, CompressMediaReducesSizeForAudio) {
    media->setType(MediaType::AUDIO); media->setFormat(MediaFormat::MP3); media->setSizeKb(2000);
    media->compressMedia();
    EXPECT_EQ(media->getSizeKb(), 2000 * 80 / 100);
}

TEST_F(MediaTest, CompressMediaReducesSizeForDocumentAndText) {
    media->setType(MediaType::DOCUMENT); media->setFormat(MediaFormat::PDF); media->setSizeKb(1500); media->compressMedia();
    EXPECT_EQ(media->getSizeKb(), 1500 * 90 / 100);
    media->setType(MediaType::TEXT); media->setFormat(MediaFormat::TXT); media->setSizeKb(1200); media->compressMedia();
    EXPECT_EQ(media->getSizeKb(), 1200 * 90 / 100);
}

TEST_F(MediaTest, CompressMediaDoesNotChangeSmallFiles) {
    media->setSizeKb(800);
    int original = media->getSizeKb();
    media->compressMedia();
    EXPECT_EQ(media->getSizeKb(), original);
}
