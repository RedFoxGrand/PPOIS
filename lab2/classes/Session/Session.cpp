#include "Session.h"

Session::Session(const string& token, const string& createdDate, const string& duration, const User& user) :
    token_(token),
    createdDate_(createdDate),
    duration_(duration),
    user_(user) {
}

void Session::setToken(const string& token) {
    token_ = token;
}
void Session::setCreatedDate(const string& createdDate) {
    createdDate_ = createdDate;
}
void Session::setDuration(const string& duration) {
    duration_ = duration;
}
void Session::setUser(const User& user) {
    user_ = user;
}

const string& Session::getToken() const {
    return token_;
}
const string& Session::getCreatedDate() const {
    return createdDate_;
}
const string& Session::getDuration() const {
    return duration_;
}
const User& Session::getUser() const {
    return user_;
}

bool Session::isValidSession() const {
    if (token_.empty()) throw SessionExpiredException("Токен сессии пуст");

    return !token_.empty() && !duration_.empty();
}

void Session::extendDuration() {
    if (token_.empty()) throw SessionExpiredException("Невозможно продлить сессию без токена");

    const int extensionSeconds = 3600;
    duration_ += to_string(extensionSeconds);
}

void Session::invalidateSession() {
    if (token_.empty()) throw SessionExpiredException("Сессия уже аннулирована");
    token_.clear();
    duration_.clear();
}
