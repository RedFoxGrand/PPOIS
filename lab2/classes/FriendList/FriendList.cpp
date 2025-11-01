#include "FriendList.h"
#include "User.h"

FriendList::FriendList(const vector<User>& friends,
                       const vector<User>& pendingRequestFriends,
                       const vector<User>& suggestedFriends) :
    friends_(friends),
    pendingRequestFriends_(pendingRequestFriends),
    suggestedFriends_(suggestedFriends) {}

void FriendList::setFriends(const vector<User>& friends) {
    friends_ = friends;
}
void FriendList::setPendingRequests(const vector<User>& pendingRequestFriends) {
    pendingRequestFriends_ = pendingRequestFriends;
}
void FriendList::setSuggestedFriends(const vector<User>& suggestedFriends) {
    suggestedFriends_ = suggestedFriends;
}

const vector<User>& FriendList::getFriends() const {
    return friends_;
}
const vector<User>& FriendList::getPendingRequests() const {
    return pendingRequestFriends_;
}
const vector<User>& FriendList::getSuggestedFriends() const {
    return suggestedFriends_;
}

void FriendList::addFriend(const User& user) {
    for (const auto& f : friends_) if (f.getId() == user.getId()) throw DuplicateUsernameException("Пользователь уже в списке друзей");
    friends_.push_back(user);
}

void FriendList::removeFriend(const User& user) {
    friends_.erase(
        remove_if(friends_.begin(), friends_.end(),
            [&](const User& u) {
                return u.getUsername() == user.getUsername();
            }),
        friends_.end());
}

void FriendList::sendFriendRequest(const User& user) {
    for (const auto& pending : pendingRequestFriends_) {
        if (pending.getUsername() == user.getUsername()) throw DuplicateUsernameException("Запрос уже отправлен пользователю");
    }
    pendingRequestFriends_.push_back(user);
}
