#pragma once
#include "InvalidMessageException.h"
#include "User.h"
#include "Message.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Chat {
public:
    Chat(const vector<Message>& messages, const User& user, const User& otherUser);

    void setUser(const User& user);
    void setOtherUser(const User& otherUser);
    void setMessages(const vector<Message>& messages);

    const User& getUser() const;
    const User& getOtherUser() const;
    const vector<Message>& getMessages() const;

    void sendMessage(const Message& message);

private:
    vector<Message> messages_;
    User user_;
    User otherUser_;
};
