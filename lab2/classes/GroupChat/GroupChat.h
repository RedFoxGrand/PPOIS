#pragma once
#include "User.h"
#include "GroupMember.h"
#include "Message.h"
#include "DuplicateUsernameException.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class GroupChat {
public:
    GroupChat(const string& nameGroup, bool isPublic, const vector<GroupMember>& participants, const vector<Message>& messages);

    void setNameGroup(const string& nameGroup);
    void setIsPublic(bool isPublic);
    void setParticipants(const vector<GroupMember>& participants);
    void setMessages(const vector<Message>& messages);

    const string& getNameGroup() const;
    bool getIsPublic() const;
    const vector<GroupMember>& getParticipants() const;
    const vector<Message>& getMessages() const;

    void addMember(const GroupMember& member);
    void removeMember(const User& user);
    int countMember(vector<GroupMember>& participants);

private:
    string nameGroup_;
    bool isPublic_;
    vector<GroupMember> participants_;
    vector<Message> messages_;
};
