#pragma once
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "Permission.h"
#include "InvalidPasswordException.h"
#include <iostream>
#include <string>
#include <exception>
#include <vector>

using namespace std;

enum class UserRole { USER, MODERATOR, ADMIN };

class User {
public:
    User(int id, const string& username, const string& email, const string& password, bool isVerified,
        const UserProfile& profile, const Settings& settings, const Wallet& wallet,
        const FriendList& friends, const BlockList& blocks, UserRole role, const vector<Permission>& permissions);

    void setId(int id);
    void setUsername(const string& username);
    void setEmail(const string& email);
    void setPassword(const string& password);
    void setVerified(bool isVerified);
    void setProfile(const UserProfile& profile);
    void setSettings(const Settings& settings);
    void setWallet(const Wallet& wallet);
    void setFriends(const FriendList& friends);
    void setBlocks(const BlockList& blocks);
    void setRole(UserRole role);
    void setPermissions(const vector<Permission>& permissions);

    int getId() const;
    const string& getUsername() const;
    const string& getEmail() const;
    const string& getPassword() const;
    bool isVerifiedUser() const;
    const UserProfile& getProfile() const;
    const Settings& getSettings() const;
    const Wallet& getWallet() const;
    const FriendList& getFriends() const;
    const BlockList& getBlocks() const;
    UserRole getRole() const;
    const vector<Permission>& getPermissions() const;

    void login(const string& password) const;
    void verifyAccount();
    void addPermission(const Permission& permission);
    void removePermission(const Permission& permission);

private:
    int id_;
    string username_;
    string email_;
    string password_;
    bool isVerified_;
    UserProfile profile_;
    Settings settings_;
    Wallet wallet_;
    FriendList friends_;
    BlockList blocks_;
    UserRole role_;
    vector<Permission> permissions_;
};
