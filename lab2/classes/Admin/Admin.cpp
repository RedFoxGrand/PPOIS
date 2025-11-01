#include "Admin.h"

Admin::Admin(const string& accessLevel, const vector<Permission>& permissions,
    const vector<Ban>& bans, const User& user) :
    accessLevel_(accessLevel),
    permissions_(permissions),
    bans_(bans),
    user_(user) {
}

void Admin::setAccessLevel(const string& accessLevel) {
    accessLevel_ = accessLevel;
}
void Admin::setPermissions(const vector<Permission>& permissions) {
    permissions_ = permissions;
}
void Admin::setBans(const vector<Ban>& bans) {
    bans_ = bans;
}
void Admin::setUser(const User& user) {
    user_ = user;
}

const string& Admin::getAccessLevel() const {
    return accessLevel_;
}
const vector<Permission>& Admin::getPermissions() const {
    return permissions_;
}
const vector<Ban>& Admin::getBans() const {
    return bans_;
}
const User& Admin::getUser() const {
    return user_;
}

void Admin::banUser(User& user, const string& reason) {
    Ban ban(reason, user);
    bans_.push_back(ban);
}

void Admin::unbanUser(int userId) {
    bans_.erase(remove_if(bans_.begin(), bans_.end(),
        [&](const Ban& ban) {
            return ban.getBannedUser().getId() == userId;
        }), bans_.end());
}
