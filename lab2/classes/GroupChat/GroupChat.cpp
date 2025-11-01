#include "GroupChat.h"

GroupChat::GroupChat(const string& nameGroup, bool isPublic, const vector<GroupMember>& participants, const vector<Message>& messages) :
    nameGroup_(nameGroup),
    isPublic_(isPublic),
    participants_(participants),
    messages_(messages) {}

int GroupChat::countMember(vector<GroupMember>& participants) {
    return static_cast<int>(participants.size());
}
void GroupChat::setNameGroup(const string& nameGroup) {
    nameGroup_ = nameGroup;
}
void GroupChat::setIsPublic(bool isPublic) {
    isPublic_ = isPublic;
}
void GroupChat::setParticipants(const vector<GroupMember>& participants) {
    participants_ = participants;
}
void GroupChat::setMessages(const vector<Message>& messages) {
    messages_ = messages;
}

const string& GroupChat::getNameGroup() const {
    return nameGroup_;
}
bool GroupChat::getIsPublic() const {
    return isPublic_;
}
const vector<GroupMember>& GroupChat::getParticipants() const {
    return participants_;
}
const vector<Message>& GroupChat::getMessages() const {
    return messages_;
}

void GroupChat::addMember(const GroupMember& member) {
    for (const auto& m : participants_) {
        if (m.getUser().getUsername() == member.getUser().getUsername()) throw DuplicateUsernameException("Участник уже состоит в группе");
    }

    participants_.push_back(member);
}

void GroupChat::removeMember(const User& user) {
    participants_.erase(remove_if(participants_.begin(), participants_.end(),
        [&](const GroupMember& m) {
            return m.getUser().getId() == user.getId();
        }), participants_.end());
}
