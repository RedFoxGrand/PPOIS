#include <gtest/gtest.h>
#include "Audio.h"

using namespace std;

class AudioTest : public ::testing::Test {
protected:
    Audio* audio;

    void SetUp() override {
        audio = new Audio(300, 70, 320, 10, "http://example.com/song.mp3", AudioFormat::MP3);
    }

    void TearDown() override {
        delete audio;
    }
};

TEST_F(AudioTest, ConstructorInitializesValuesCorrectly) {
    EXPECT_EQ(audio->getDuration(), 300);
    EXPECT_EQ(audio->getSoundVolume(), 70);
    EXPECT_EQ(audio->getBitrate(), 320);
    EXPECT_EQ(audio->getSizeMb(), 10);
    EXPECT_EQ(audio->getUrl(), "http://example.com/song.mp3");
    EXPECT_EQ(audio->getFormat(), AudioFormat::MP3);
}

TEST_F(AudioTest, SettersUpdateValuesCorrectly) {
    audio->setDuration(250);
    audio->setSoundVolume(85);
    audio->setBitrate(256);
    audio->setSizeMb(8);
    audio->setUrl("http://newurl.com/audio.aac");
    audio->setFormat(AudioFormat::AAC);

    EXPECT_EQ(audio->getDuration(), 250);
    EXPECT_EQ(audio->getSoundVolume(), 85);
    EXPECT_EQ(audio->getBitrate(), 256);
    EXPECT_EQ(audio->getSizeMb(), 8);
    EXPECT_EQ(audio->getUrl(), "http://newurl.com/audio.aac");
    EXPECT_EQ(audio->getFormat(), AudioFormat::AAC);
}

TEST_F(AudioTest, FindoutFormatReturnsCorrectString) {
    audio->setFormat(AudioFormat::MP3);
    EXPECT_EQ(audio->findoutFormat(), "MP3");

    audio->setFormat(AudioFormat::AAC);
    EXPECT_EQ(audio->findoutFormat(), "AAC");

    audio->setFormat(AudioFormat::WAV);
    EXPECT_EQ(audio->findoutFormat(), "WAV");

    audio->setFormat(AudioFormat::FLAC);
    EXPECT_EQ(audio->findoutFormat(), "FLAC");
}

TEST_F(AudioTest, ChangeVolumeChangesSoundVolume) {
    audio->changeVolume(90);
    EXPECT_EQ(audio->getSoundVolume(), 90);

    audio->changeVolume(0);
    EXPECT_EQ(audio->getSoundVolume(), 0);
}

TEST_F(AudioTest, UrlCanBeUpdated) {
    string newUrl = "https://music.example.org/track.wav";
    audio->setUrl(newUrl);
    EXPECT_EQ(audio->getUrl(), newUrl);
}
