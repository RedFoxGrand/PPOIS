#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "ContactInfo.h"

using namespace std;

class Person {
public:
    Person(const string& name, const string& surname, time_t birthDate, const ContactInfo& data);

    void setName(const string& name);
    void setSurname(const string& surname);
    void setBirthDate(time_t birthDate);
    void setContactInfo(const ContactInfo& data);

    const string& getName() const;
    const string& getSurname() const;
    time_t getBirthDate() const;
    const ContactInfo& getContactInfo() const;

    string getFullName() const;
    int getAge() const;

protected:
    string name_;
    string surname_;
    time_t birthDate_;
    ContactInfo data_;
};
