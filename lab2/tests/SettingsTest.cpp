#include <gtest/gtest.h>
#include "Settings.h"
#include "Exception.h"

using namespace std;

class SettingsTest : public ::testing::Test {
protected:
    void SetUp() override {
        settings = new Settings(14, "Russian", true, true, true, false, DARK);
    }

    void TearDown() override {
        delete settings;
    }

    Settings* settings;
};

TEST_F(SettingsTest, GettersReturnCorrectValues) {
    EXPECT_EQ(settings->getFontSize(), 14);
    EXPECT_EQ(settings->getLanguage(), "Russian");
    EXPECT_TRUE(settings->isPrivateProfile());
    EXPECT_TRUE(settings->isReceivingNotifications());
    EXPECT_TRUE(settings->isProfileVisible());
    EXPECT_FALSE(settings->isPhoneVisible());
    EXPECT_EQ(settings->getTheme(), DARK);
}

TEST_F(SettingsTest, SettersUpdateValues) {
    settings->setFontSize(20);
    settings->setLanguage("English");
    settings->setPrivate(false);
    settings->setReceiveNotifications(false);
    settings->setProfileVisibility(false);
    settings->setShowPhone(true);
    settings->setTheme(LIGHT);

    EXPECT_EQ(settings->getFontSize(), 20);
    EXPECT_EQ(settings->getLanguage(), "English");
    EXPECT_FALSE(settings->isPrivateProfile());
    EXPECT_FALSE(settings->isReceivingNotifications());
    EXPECT_FALSE(settings->isProfileVisible());
    EXPECT_TRUE(settings->isPhoneVisible());
    EXPECT_EQ(settings->getTheme(), LIGHT);
}

TEST_F(SettingsTest, ApplyThemePrintsCorrectMessage) {
    testing::internal::CaptureStdout();
    settings->applyTheme(SYSTEM);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(settings->getTheme(), SYSTEM);
}

TEST_F(SettingsTest, ToggleNotificationsSwitchesStateAndPrints) {
    EXPECT_TRUE(settings->isReceivingNotifications());

    testing::internal::CaptureStdout();
    settings->toggleNotifications();
    string output1 = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(settings->isReceivingNotifications());

    testing::internal::CaptureStdout();
    settings->toggleNotifications();
    string output2 = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(settings->isReceivingNotifications());
}

TEST_F(SettingsTest, ChangeFontSizeWorksForValidSize) {
    testing::internal::CaptureStdout();
    int newSize = settings->changeFontSize(18);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(newSize, 18);
    EXPECT_EQ(settings->getFontSize(), 18);
}

TEST_F(SettingsTest, ChangeFontSizeThrowsForInvalidSize) {
    EXPECT_THROW(settings->changeFontSize(5), InvalidFontSizeException);
    EXPECT_THROW(settings->changeFontSize(100), InvalidFontSizeException);
}

TEST_F(SettingsTest, ToggleShowPhoneChangesStateAndPrints) {
    EXPECT_FALSE(settings->isPhoneVisible());

    testing::internal::CaptureStdout();
    bool newState1 = settings->toggleShowPhone();
    string output1 = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(newState1);
    EXPECT_TRUE(settings->isPhoneVisible());

    testing::internal::CaptureStdout();
    bool newState2 = settings->toggleShowPhone();
    string output2 = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(newState2);
    EXPECT_FALSE(settings->isPhoneVisible());
}
