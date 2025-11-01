#pragma once
#include <iostream>
#include <string>

using namespace std;

class ContactInfo {
public:
    ContactInfo(const string& email, const string& phone, const string& address);

    void setEmail(const string& email);
    void setPhone(const string& phone);
    void setAddress(const string& address);

    const string& getEmail() const;
    const string& getPhone() const;
    const string& getAddress() const;

    string changeEmail(const string& newEmail);

private:
    string email_;
    string phone_;
    string address_;
};
