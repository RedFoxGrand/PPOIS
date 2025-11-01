#pragma once
#include "InvalidPasswordException.h"
#include "InvalidEmailFormatException.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class PasswordManager {
public:
    PasswordManager(bool autofillPassword, bool showPassword, const vector<string>& passwordHistory);

    void setAutofill(bool autofillPassword);
    void setShowPassword(bool showPassword);
    void setPasswordHistory(const vector<string>& passwordHistory);

    bool isAutofillEnabled() const;
    bool isPasswordVisible() const;
    const vector<string>& getPasswordHistory() const;

    bool verifyPassword(const string& input);
    void changePassword(const string& newPassword);
    void resetPassword(const string& email);

private:
    bool autofillPassword_;
    bool showPassword_;
    vector<string> passwordHistory_;
};
