#include "UserProfile.h"

UserProfile::UserProfile(const string& firstName, const string& lastName, const string& birthDate,
                         const string& registrationDate, const string& phone,
                         const string& country, const string& city,
                         const vector<string>& interests) : 
    firstName_(firstName), 
    lastName_(lastName), 
    birthDate_(birthDate),
    registrationDate_(registrationDate), 
    phone_(phone),
    country_(country), 
    city_(city), 
    interests_(interests) {}

void UserProfile::setFirstName(const string& firstName) { 
    firstName_ = firstName; 
}
void UserProfile::setLastName(const string& lastName) { 
    lastName_ = lastName; 
}
void UserProfile::setBirthDate(const string& birthDate) { 
    birthDate_ = birthDate; 
}
void UserProfile::setRegistrationDate(const string& registrationDate) { 
    registrationDate_ = registrationDate; 
}
void UserProfile::setPhone(const string& phone) { 
    phone_ = phone; 
}
void UserProfile::setCountry(const string& country) { 
    country_ = country; 
}
void UserProfile::setCity(const string& city) { 
    city_ = city; 
}
void UserProfile::setInterests(const vector<string>& interests) { 
    interests_ = interests; 
}

const string& UserProfile::getFirstName() const { 
    return firstName_; 
}
const string& UserProfile::getLastName() const { 
    return lastName_; 
}
const string& UserProfile::getBirthDate() const { 
    return birthDate_; 
}
const string& UserProfile::getRegistrationDate() const { 
    return registrationDate_; 
}
const string& UserProfile::getPhone() const { 
    return phone_; 
}
const string& UserProfile::getCountry() const { 
    return country_; 
}
const string& UserProfile::getCity() const { 
    return city_; 
}
const vector<string>& UserProfile::getInterests() const {
    return interests_; 
}

void UserProfile::updateProfile(const UserProfile& newProfile) {
    firstName_ = newProfile.firstName_;
    lastName_ = newProfile.lastName_;
    birthDate_ = newProfile.birthDate_;
    registrationDate_ = newProfile.registrationDate_;
    phone_ = newProfile.phone_;
    country_ = newProfile.country_;
    city_ = newProfile.city_;
    interests_ = newProfile.interests_;
}

void UserProfile::printProfileInfo() const {
    cout << "Имя и фамилия: " << firstName_ << " " << lastName_ << endl;
    cout << "Дата рождения: " << birthDate_ << endl;
    cout << "Дата регистрации: " << registrationDate_ << endl;
    cout << "Телефон: " << phone_ << endl;
    cout << "Страна: " << country_ << endl;
    cout << "Город: " << city_ << endl;
    cout << "Интересы: ";
    if (interests_.empty())  cout << "нет интересов" << endl;
    else {
        for (size_t i = 0; i < interests_.size(); i++) {
            cout << interests_[i];
            if (i < interests_.size() - 1) cout << ", ";
        }
        cout << endl;
    }
    cout << endl;
}
