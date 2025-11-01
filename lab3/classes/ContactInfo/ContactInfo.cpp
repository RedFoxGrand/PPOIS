#include "ContactInfo.h"

ContactInfo::ContactInfo(const string& email, const string& phone, const string& address) : 
    email_(email), 
    phone_(phone), 
    address_(address) {
}

void ContactInfo::setEmail(const string& email) { 
    email_ = email; 
}
void ContactInfo::setPhone(const string& phone) { 
    phone_ = phone; 
}
void ContactInfo::setAddress(const string& address) { 
    address_ = address; 
}

const string& ContactInfo::getEmail() const { 
    return email_; 
}
const string& ContactInfo::getPhone() const { 
    return phone_; 
}
const string& ContactInfo::getAddress() const { 
    return address_; 
}

string ContactInfo::changeEmail(const string& newEmail) {
    if (newEmail.find('@') == string::npos || newEmail.find('.') == string::npos) return email_;

    string oldEmail = email_;
    email_ = newEmail;

    return oldEmail;
}

