#include "Permission.h"
#include "User.h"

Permission::Permission(const string& name, const string& description, bool isRevocable) :
    name_(name),
    description_(description),
    isRevocable_(isRevocable) {
}

void Permission::setName(const string& name) {
    name_ = name;
}

void Permission::setDescription(const string& description) {
    description_ = description;
}

void Permission::setRevocable(bool isRevocable) {
    isRevocable_ = isRevocable;
}

const string& Permission::getName() const {
    return name_;
}

const string& Permission::getDescription() const {
    return description_;
}

bool Permission::getRevocable() const {
    return isRevocable_;
}

void Permission::grantTo(User& user) {
    user.addPermission(*this);
}

void Permission::revokeFrom(User& user) {
    if (isRevocable_) user.removePermission(*this);
}
