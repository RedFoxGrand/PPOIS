#include "Person.h"

Person::Person(const string& name, const string& surname, time_t birthDate, const ContactInfo& data)
    : name_(name), 
    surname_(surname), 
    birthDate_(birthDate), 
    data_(data) {
}

void Person::setName(const string& name) {
    name_ = name;
}

void Person::setSurname(const string& surname) {
    surname_ = surname;
}

void Person::setBirthDate(time_t birthDate) {
    birthDate_ = birthDate;
}

void Person::setContactInfo(const ContactInfo& data) {
    data_ = data;
}

const string& Person::getName() const { 
    return name_;
}
const string& Person::getSurname() const { 
    return surname_; 
}
time_t Person::getBirthDate() const {
    return birthDate_; 
}
const ContactInfo& Person::getContactInfo() const {
    return data_; 
}

string Person::getFullName() const {
    return name_ + " " + surname_;
}

int Person::getAge() const {
    time_t now = time(nullptr);
    double seconds = difftime(now, birthDate_);
    int years = static_cast<int>(seconds / (60 * 60 * 24 * 365.25));
    return years;
}

