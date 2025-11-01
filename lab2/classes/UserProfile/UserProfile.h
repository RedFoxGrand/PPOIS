#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class UserProfile {
public:
    UserProfile(const string& firstName, const string& lastName, const string& birthDate,
                const string& registrationDate, const string& phone,
                const string& country, const string& city,
                const vector<string>& interests);
    
    void setFirstName(const string& firstName);
    void setLastName(const string& lastName);
    void setBirthDate(const string& birthDate);
    void setRegistrationDate(const string& registrationDate);
    void setPhone(const string& phone);
    void setCountry(const string& country);
    void setCity(const string& city);
    void setInterests(const vector<string>& interests);

    const string& getFirstName() const;
    const string& getLastName() const;
    const string& getBirthDate() const;
    const string& getRegistrationDate() const;
    const string& getPhone() const;
    const string& getCountry() const;
    const string& getCity() const;
    const vector<string>& getInterests() const;

    void updateProfile(const UserProfile& newProfile);
    void printProfileInfo() const;

private:
    string firstName_;
    string lastName_;
    string birthDate_; 
    string registrationDate_; 
    string phone_; 
    string country_; 
    string city_;
    vector<string> interests_;
};
