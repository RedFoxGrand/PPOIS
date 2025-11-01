#include "Message.h"

Message::Message(const string& content, const string& timestamp, bool isEdited,
                 const User& sender, const User& recipient, MessageType messageType, MessageStatus status) :
    content_(content),
    timestamp_(timestamp),
    isEdited_(isEdited),
    sender_(sender),
    recipient_(recipient),
    messageType_(messageType),
    status_(status) {
}

void Message::setContent(const string& content) {
    content_ = content;
}
void Message::setTimestamp(const string& timestamp) {
    timestamp_ = timestamp;
}
void Message::setEdited(bool isEdited) {
    isEdited_ = isEdited;
}
void Message::setSender(const User& sender) {
    sender_ = sender;
}
void Message::setRecipient(const User& recipient) {
    recipient_ = recipient;
}
void Message::setMessageType(MessageType messageType) {
    messageType_ = messageType;
}
void Message::setStatus(MessageStatus status) {
    status_ = status;
}

const string& Message::getContent() const {
    return content_;
}
const string& Message::getTimestamp() const {
    return timestamp_;
}
bool Message::getEdited() const {
    return isEdited_;
}
const User& Message::getSender() const {
    return sender_;
}
const User& Message::getRecipient() const {
    return recipient_;
}
MessageType Message::getMessageType() const {
    return messageType_;
}
MessageStatus Message::getStatus() const {
    return status_;
}

void Message::editMessage(const string& newContent) {
    if (newContent.empty()) throw InvalidMessageException("Сообщение не может быть пустым");
    if (newContent == content_) throw InvalidMessageException("Новое содержимое совпадает с текущим. Редактирование отменено");

    content_ = newContent;
    isEdited_ = true;
}
