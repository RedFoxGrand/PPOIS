#include "User.h"
#include "Exception.h"

User::User(int id, const string& username, const string& email, const string& password, bool isVerified,
           const UserProfile& profile, const Settings& settings, const Wallet& wallet,
           const FriendList& friends, const BlockList& blocks, UserRole role, const vector<Permission>& permissions) :
    id_(id), 
    username_(username), 
    email_(email), 
    password_(password),
    isVerified_(isVerified), 
    profile_(profile), 
    settings_(settings),
    wallet_(wallet), 
    friends_(friends), 
    blocks_(blocks), 
    role_(role),
    permissions_(permissions){}

void User::setId(int id) { 
    id_ = id; 
}
void User::setUsername(const string& username) { 
    username_ = username;
}
void User::setEmail(const string& email) { 
    email_ = email;
}
void User::setPassword(const string& password) { 
    password_ = password;
}
void User::setVerified(bool isVerified) {
    isVerified_ = isVerified;
}
void User::setProfile(const UserProfile& profile) {
    profile_ = profile;
}
void User::setSettings(const Settings& settings) {
    settings_ = settings;
}
void User::setWallet(const Wallet& wallet) {
    wallet_ = wallet;
}
void User::setFriends(const FriendList& friends) {
    friends_ = friends;
}
void User::setBlocks(const BlockList& blocks) {
    blocks_ = blocks;
}
void User::setRole(UserRole role) {
    role_ = role;
}
void User::setPermissions(const vector<Permission>& permissions) {
    permissions_ = permissions;
}

int User::getId() const { 
    return id_;
}
const string& User::getUsername() const { 
    return username_;
}
const string& User::getEmail() const { 
    return email_;
}
const string& User::getPassword() const { 
    return password_;
}
bool User::isVerifiedUser() const { 
    return isVerified_;
}
const UserProfile& User::getProfile() const { 
    return profile_;
}
const Settings& User::getSettings() const { 
    return settings_;
}
const Wallet& User::getWallet() const { 
    return wallet_;
}
const FriendList& User::getFriends() const { 
    return friends_;
}
const BlockList& User::getBlocks() const { 
    return blocks_;
}
UserRole User::getRole() const {
    return role_;
}
const vector<Permission>& User::getPermissions() const {
    return permissions_;
}

void User::login(const string& password) const {
    if (!isVerified_) throw InvalidPasswordException("Аккаунт не подтверждён");
    if (password_ != password) throw InvalidPasswordException("Неверный пароль");
}

void User::verifyAccount() {
    if (!isVerified_) isVerified_ = true;
}


void User::addPermission(const Permission& permission) {
    permissions_.push_back(permission);
}

void User::removePermission(const Permission& permission) {
    permissions_.erase(
        remove_if(permissions_.begin(), permissions_.end(),
            [&](const Permission& p) {
                return p.getName() == permission.getName();
            }),
        permissions_.end());
}
