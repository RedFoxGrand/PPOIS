#include "Chat.h"

Chat::Chat(const vector<Message>& messages, const User& user, const User& otherUser) :
    messages_(messages),
    user_(user),
    otherUser_(otherUser) {
}

void Chat::setUser(const User& user) {
    user_ = user;
}

void Chat::setOtherUser(const User& otherUser) {
    otherUser_ = otherUser;
}

void Chat::setMessages(const vector<Message>& messages) {
    messages_ = messages;
}

const User& Chat::getUser() const {
    return user_;
}

const User& Chat::getOtherUser() const {
    return otherUser_;
}

const vector<Message>& Chat::getMessages() const {
    return messages_;
}

void Chat::sendMessage(const Message& message) {
    if (message.getContent().empty()) throw InvalidMessageException("Сообщение не может быть пустым");
    if (message.getSender().getUsername() == message.getRecipient().getUsername()) throw InvalidMessageException("Нельзя отправить сообщение самому себе");

    messages_.push_back(message);
}
