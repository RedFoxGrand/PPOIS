#include "GroupMember.h"

GroupMember::GroupMember(const string& joinedDate, GroupRole role, const User& user) :
    joinedDate_(joinedDate),
    role_(role),
    user_(user) {
}

void GroupMember::setJoinedDate(const string& joinedDate) {
    joinedDate_ = joinedDate;
}
void GroupMember::setRole(GroupRole role) {
    role_ = role;
}
void GroupMember::setUser(const User& user) {
    user_ = user;
}

const string& GroupMember::getJoinedDate() const {
    return joinedDate_;
}
GroupRole GroupMember::getRole() const {
    return role_;
}
const User& GroupMember::getUser() const {
    return user_;
}

string GroupMember::roleToString(GroupRole role) {
    switch (role) {
    case GroupRole::MEMBER: return "участник";
    case GroupRole::MODERATOR: return "модератор";
    case GroupRole::ADMIN: return "администратор";
    default: return "неизвестная роль";
    }
}

void GroupMember::promoteToAdmin() {
    if (role_ == GroupRole::ADMIN)  return;

    role_ = GroupRole::ADMIN;
}

void GroupMember::demoteFromAdmin() {
    if (role_ != GroupRole::ADMIN)  return;

    role_ = GroupRole::MEMBER;
}
