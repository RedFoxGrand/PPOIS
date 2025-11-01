#include "PasswordManager.h"

PasswordManager::PasswordManager(bool autofillPassword, bool showPassword, const vector<string>& passwordHistory) :
    autofillPassword_(autofillPassword),
    showPassword_(showPassword),
    passwordHistory_(passwordHistory) {}

void PasswordManager::setAutofill(bool autofillPassword) {
    autofillPassword_ = autofillPassword;
}
void PasswordManager::setShowPassword(bool showPassword) {
    showPassword_ = showPassword;
}
void PasswordManager::setPasswordHistory(const vector<string>& passwordHistory) {
    passwordHistory_ = passwordHistory;
}

bool PasswordManager::isAutofillEnabled() const {
    return autofillPassword_;
}
bool PasswordManager::isPasswordVisible() const {
    return showPassword_;
}
const vector<string>& PasswordManager::getPasswordHistory() const {
    return passwordHistory_;
}

bool PasswordManager::verifyPassword(const string& input) {
    if (passwordHistory_.empty()) return false;

    bool result = passwordHistory_.back() == input;

    return result;
}

void PasswordManager::changePassword(const string& newPassword) {
    if (newPassword.empty()) throw InvalidPasswordException("Новый пароль не может быть пустым");
    if (!passwordHistory_.empty() && passwordHistory_.back() == newPassword) throw InvalidPasswordException("Новый пароль совпадает с текущим. Изменение отменено");

    passwordHistory_.push_back(newPassword);
}

void PasswordManager::resetPassword(const string& email) {
    if (email.empty()) throw InvalidEmailFormatException("Email не может быть пустым");
    if (email.find('@') == string::npos || email.find('.') == string::npos) throw InvalidEmailFormatException("Некорректный формат email");
}
