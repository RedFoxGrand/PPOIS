#include "Employee.h"
#include "Flight.h"

Employee::Employee(const string& name, const string& surname, time_t birthDate,
    const ContactInfo& data, double salary, bool isAvailable) : 
    Person(name, surname, birthDate, data),
    salary_(salary),
    isAvailable_(isAvailable) {
}

void Employee::setSalary(double salary) { 
    salary_ = salary; 
}
void Employee::setIsAvailable(bool isAvailable) { 
    isAvailable_ = isAvailable; 
}

double Employee::getSalary() const { 
    return salary_; 
}
bool Employee::getIsAvailable() const { 
    return isAvailable_; 
}

void Employee::markUnavailable() {
    isAvailable_ = false;
}
