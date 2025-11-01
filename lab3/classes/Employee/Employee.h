#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "Person.h"

using namespace std;

class Flight;

class Employee : public Person {
public:
    Employee(const string& name, const string& surname, time_t birthDate,
        const ContactInfo& data, double salary, bool isAvailable);

    void setSalary(double salary);
    void setIsAvailable(bool isAvailable);

    double getSalary() const;
    bool getIsAvailable() const;

    void markUnavailable();

protected:
    double salary_;
    bool isAvailable_;
};
