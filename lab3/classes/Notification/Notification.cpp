#include "Notification.h"

Notification::Notification(const Passenger& recipient, const string& message, time_t timestamp, bool isRead) : 
    recipient_(recipient), 
    message_(message), 
    timestamp_(timestamp), 
    isRead_(isRead) {
}

void Notification::setRecipient(const Passenger& recipient) { 
    recipient_ = recipient; 
}
void Notification::setMessage(const string& message) { 
    message_ = message; 
}
void Notification::setTimestamp(time_t timestamp) { 
    timestamp_ = timestamp; 
}
void Notification::setIsRead(bool isRead) {
    isRead_ = isRead; 
}

const Passenger& Notification::getRecipient() const {
    return recipient_; 
}
const string& Notification::getMessage() const { 
    return message_; 
}
time_t Notification::getTimestamp() const { 
    return timestamp_; 
}
bool Notification::getIsRead() const { 
    return isRead_; 
}

void Notification::markAsRead() {
    isRead_ = true;
}
