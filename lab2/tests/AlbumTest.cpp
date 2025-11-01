#include <gtest/gtest.h>
#include "Album.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "Permission.h"
#include "Currency.h"
#include "Photo.h"
#include "Video.h"
#include "Audio.h"

using namespace std;

class AlbumTest : public ::testing::Test {
protected:
    UserProfile* profile; Settings* settings; Currency* currency; Wallet* wallet;
    FriendList* friends; BlockList* blocks; vector<Permission>* permissions; User* user;
    Photo* photo; Video* video; Audio* audio;
    vector<Photo>* photos; vector<Video>* videos; vector<Audio>* audios;
    Album* album;

    void SetUp() override {
        profile = new UserProfile("Иван", "Иванов", "12.01.2007", "01.09.2023",
            "+375291234567", "Беларусь", "Минск", { "Игры", "Программирование" });
        settings = new Settings(18, "Русский", true, true, false, true, Theme::LIGHT);
        currency = new Currency("BYN", "Белорусский рубль", 1.0);
        wallet = new Wallet(10000.0, {}, {}, *currency);
        friends = new FriendList({}, {}, {});
        blocks = new BlockList({}, {});
        permissions = new vector<Permission>{
            Permission("READ", "Чтение", true),
            Permission("WRITE", "Изменение", true)
        };

        user = new User(1, "ivan", "ivan@example.com", "12345", true,
            *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);

        photo = new Photo(2048, "https://example.com/photo.jpg", PhotoFormat::JPEG, { 1920, 1080 });
        video = new Video(120, 70, 2000, 500, "https://example.com/video.mp4", true, VideoFormat::MP4, { 1280, 720 });
        audio = new Audio(180, 80, 320, 10, "https://example.com/audio.mp3", AudioFormat::MP3);

        photos = new vector<Photo>{ *photo };
        videos = new vector<Video>{ *video };
        audios = new vector<Audio>{ *audio };

        album = new Album("Путешествие в Сочи", *user, *photos, *videos, *audios);
    }

    void TearDown() override {
        delete album; delete audios; delete videos; delete photos;
        delete audio; delete video; delete photo;
        delete user; delete permissions; delete blocks;
        delete friends; delete wallet; delete currency;
        delete settings; delete profile;
    }
};

/// Проверка конструктора
TEST_F(AlbumTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(album->getTitle(), "Путешествие в Сочи");
    EXPECT_EQ(album->getOwner().getUsername(), "ivan");
    EXPECT_EQ(album->getPhotos().size(), 1);
    EXPECT_EQ(album->getVideos().size(), 1);
    EXPECT_EQ(album->getAudios().size(), 1);
    EXPECT_EQ(album->getPhotos()[0].getUrl(), "https://example.com/photo.jpg");
    EXPECT_EQ(album->getVideos()[0].getUrl(), "https://example.com/video.mp4");
    EXPECT_EQ(album->getAudios()[0].getUrl(), "https://example.com/audio.mp3");
}

/// Проверка работы сеттеров
TEST_F(AlbumTest, SettersWorkCorrectly) {
    UserProfile newProfile("Петр", "Петров", "02.02.1990", "01.01.2022",
        "+79991112233", "Россия", "Казань", { "Музыка" });
    Settings newSettings(25, "English", false, false, true, false, Theme::DARK);
    Currency newCurrency("USD", "Доллар", 90.0);
    Wallet newWallet(2000.0, {}, {}, newCurrency);
    FriendList newFriends({}, {}, {});
    BlockList newBlocks({}, {});
    vector<Permission> newPermissions{ Permission("ADMIN", "Полные права", true) };
    User newUser(2, "petr", "petr@example.com", "98765", false,
        newProfile, newSettings, newWallet, newFriends, newBlocks, UserRole::MODERATOR, newPermissions);

    vector<Photo> newPhotos{ Photo(512, "https://example.com/newphoto.png", PhotoFormat::PNG, {800, 600}) };
    vector<Video> newVideos{ Video(60, 80, 1500, 300, "https://example.com/newvideo.mov", false, VideoFormat::MOV, {640, 480}) };
    vector<Audio> newAudios{ Audio(90, 60, 256, 5, "https://example.com/newaudio.aac", AudioFormat::AAC) };

    album->setTitle("Новый альбом");
    album->setOwner(newUser);
    album->setPhotos(newPhotos);
    album->setVideos(newVideos);
    album->setAudios(newAudios);

    EXPECT_EQ(album->getTitle(), "Новый альбом");
    EXPECT_EQ(album->getOwner().getUsername(), "petr");
    EXPECT_EQ(album->getPhotos().size(), 1);
    EXPECT_EQ(album->getVideos().size(), 1);
    EXPECT_EQ(album->getAudios().size(), 1);
    EXPECT_EQ(album->getPhotos()[0].getUrl(), "https://example.com/newphoto.png");
    EXPECT_EQ(album->getVideos()[0].getUrl(), "https://example.com/newvideo.mov");
    EXPECT_EQ(album->getAudios()[0].getUrl(), "https://example.com/newaudio.aac");
}

TEST_F(AlbumTest, AddMediaWorksCorrectly) {
    Photo extraPhoto(1024, "https://example.com/additional.jpg", PhotoFormat::JPEG, { 1024, 768 });
    Video extraVideo(300, 60, 2500, 700, "https://example.com/additional.mp4", false, VideoFormat::MP4, { 1920, 1080 });
    Audio extraAudio(200, 90, 320, 15, "https://example.com/additional.wav", AudioFormat::WAV);

    album->addPhoto(extraPhoto);
    album->addVideo(extraVideo);
    album->addAudio(extraAudio);

    EXPECT_EQ(album->getPhotos().size(), 2);
    EXPECT_EQ(album->getVideos().size(), 2);
    EXPECT_EQ(album->getAudios().size(), 2);
    EXPECT_EQ(album->getPhotos().back().getUrl(), "https://example.com/additional.jpg");
    EXPECT_EQ(album->getVideos().back().getUrl(), "https://example.com/additional.mp4");
    EXPECT_EQ(album->getAudios().back().getUrl(), "https://example.com/additional.wav");
}

TEST_F(AlbumTest, OwnerDataIsConsistent) {
    const User& owner = album->getOwner();
    EXPECT_EQ(owner.getEmail(), "ivan@example.com");
    EXPECT_TRUE(owner.isVerifiedUser());
    EXPECT_EQ(owner.getProfile().getFirstName(), "Иван");
    EXPECT_EQ(owner.getProfile().getCity(), "Минск");
}
