#pragma once
#include "InvalidFontSizeException.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

enum Theme { LIGHT, DARK, SYSTEM };

class Settings {
public:
    Settings(int fontSize, const string& language, bool isPrivate,
        bool receiveNotifications, bool profileVisibility, bool showPhone, Theme theme);

    void setFontSize(int fontSize);
    void setLanguage(const string& language);
    void setPrivate(bool isPrivate);
    void setReceiveNotifications(bool receiveNotifications);
    void setProfileVisibility(bool profileVisibility);
    void setShowPhone(bool showPhone);
    void setTheme(Theme theme);

    int getFontSize() const;
    const string& getLanguage() const;
    bool isPrivateProfile() const;
    bool isReceivingNotifications() const;
    bool isProfileVisible() const;
    bool isPhoneVisible() const;
    Theme getTheme() const;

    void applyTheme(Theme newTheme);
    void toggleNotifications();
    int changeFontSize(int newSize);
    bool toggleShowPhone();

private:
    int fontSize_;
    string language_;
    bool isPrivate_;
    bool receiveNotifications_;
    bool profileVisibility_;
    bool showPhone_;
    Theme theme_;
};
