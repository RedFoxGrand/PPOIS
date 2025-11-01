#pragma once
#include "User.h"
#include "InvalidMessageException.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

enum class MessageType { TEXT, PHOTO, VIDEO, AUDIO, FILE };
enum class MessageStatus { SENT, DELIVERED, READ };

class Message {
public:
    Message(const string& content, const string& timestamp, bool isEdited,
        const User& sender, const User& recipient, MessageType messageType, MessageStatus status);

    void setContent(const string& content);
    void setTimestamp(const string& timestamp);
    void setEdited(bool isEdited);
    void setSender(const User& sender);
    void setRecipient(const User& recipient);
    void setMessageType(MessageType messageType);
    void setStatus(MessageStatus status);

    const string& getContent() const;
    const string& getTimestamp() const;
    bool getEdited() const;
    const User& getSender() const;
    const User& getRecipient() const;
    MessageType getMessageType() const;
    MessageStatus getStatus() const;

    void editMessage(const string& newContent);

private:
    string content_;
    string timestamp_;
    bool isEdited_;
    User sender_;
    User recipient_;
    MessageType messageType_;
    MessageStatus status_;
};
