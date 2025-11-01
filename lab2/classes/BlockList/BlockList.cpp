#include "BlockList.h"
#include "User.h"

BlockList::BlockList(const vector<User>& blockedUsers, const vector<string>& reasons) :
    blockedUsers_(blockedUsers),
    reasons_(reasons) {}

void BlockList::setBlockedUsers(const vector<User>& blockedUsers) {
    blockedUsers_ = blockedUsers;
}
void BlockList::setBlockReasons(const vector<string>& reasons) {
    reasons_ = reasons;
}

const vector<User>& BlockList::getBlockedUsers() const {
    return blockedUsers_;
}
const vector<string>& BlockList::getBlockReasons() const {
    return reasons_;
}

void BlockList::blockUser(const User& user, const string& reason) {
    for (const auto& b : blockedUsers_) {
        if (b.getUsername() == user.getUsername()) throw DuplicateUsernameException("Пользователь уже заблокирован");
    }

    blockedUsers_.push_back(user);
    reasons_.push_back(reason);
}

void BlockList::unblockUser(const User& user) {
    auto it = find_if(blockedUsers_.begin(), blockedUsers_.end(),
        [&](const User& b) {
            return b.getUsername() == user.getUsername();
        });

    if (it != blockedUsers_.end()) blockedUsers_.erase(it);
}
