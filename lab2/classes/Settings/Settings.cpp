#include "Settings.h"

Settings::Settings(int fontSize, const string& language, bool isPrivate,
                   bool receiveNotifications, bool profileVisibility, bool showPhone, Theme theme) :
    fontSize_(fontSize),
    language_(language),
    isPrivate_(isPrivate),
    receiveNotifications_(receiveNotifications),
    profileVisibility_(profileVisibility),
    showPhone_(showPhone),
    theme_(theme) {}

void Settings::setFontSize(int fontSize) {
    fontSize_ = fontSize;
}
void Settings::setLanguage(const string& language) {
    language_ = language;
}
void Settings::setPrivate(bool isPrivate) {
    isPrivate_ = isPrivate;
}
void Settings::setReceiveNotifications(bool receiveNotifications) {
    receiveNotifications_ = receiveNotifications;
}
void Settings::setProfileVisibility(bool profileVisibility) {
    profileVisibility_ = profileVisibility;
}
void Settings::setShowPhone(bool showPhone) {
    showPhone_ = showPhone;
}
void Settings::setTheme(Theme theme) {
    theme_ = theme;
}

int Settings::getFontSize() const {
    return fontSize_;
}
const string& Settings::getLanguage() const {
    return language_;
}
bool Settings::isPrivateProfile() const {
    return isPrivate_;
}
bool Settings::isReceivingNotifications() const {
    return receiveNotifications_;
}
bool Settings::isProfileVisible() const {
    return profileVisibility_;
}
bool Settings::isPhoneVisible() const {
    return showPhone_;
}
Theme Settings::getTheme() const {
    return theme_;
}

void Settings::applyTheme(Theme newTheme) {
    theme_ = newTheme;

    string themeName;
    switch (newTheme) {
    case LIGHT: themeName = "LIGHT"; break;
    case DARK: themeName = "DARK"; break;
    case SYSTEM: themeName = "SYSTEM"; break;
    default: themeName = "НЕИЗВЕСТНА"; break;
    }
}

void Settings::toggleNotifications() {
    receiveNotifications_ = !receiveNotifications_;
}

int Settings::changeFontSize(int newSize) {
    if (newSize >= 8 && newSize <= 32) {
        fontSize_ = newSize;

        return fontSize_;
    }
    else throw InvalidFontSizeException("Размер шрифта должен быть от 8 до 32");
}

bool Settings::toggleShowPhone() {
    showPhone_ = !showPhone_;

    return showPhone_;
}
