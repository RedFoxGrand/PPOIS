#include <gtest/gtest.h>
#include "Employee.h"

using namespace std;

class EmployeeTest : public ::testing::Test {
protected:
    Employee* employee;
    ContactInfo* contact;
    time_t birthDate;

    void SetUp() override {
        contact = new ContactInfo("user@mail.com", "+79995553322", "Москва, ул. Тверская, 5");

        tm birth = {};
        birth.tm_year = 1990 - 1900;
        birth.tm_mon = 3;
        birth.tm_mday = 10;
        birthDate = mktime(&birth);

        employee = new Employee("Анна", "Смирнова", birthDate, *contact, 75000.0, true);
    }

    void TearDown() override {
        delete employee; delete contact;
    }
};

TEST_F(EmployeeTest, ConstructorInitializesValuesCorrectly) {
    EXPECT_EQ(employee->getName(), "Анна");
    EXPECT_EQ(employee->getSurname(), "Смирнова");
    EXPECT_EQ(employee->getBirthDate(), birthDate);
    EXPECT_EQ(employee->getContactInfo().getEmail(), "user@mail.com");
    EXPECT_EQ(employee->getContactInfo().getPhone(), "+79995553322");
    EXPECT_EQ(employee->getContactInfo().getAddress(), "Москва, ул. Тверская, 5");
    EXPECT_DOUBLE_EQ(employee->getSalary(), 75000.0);
    EXPECT_TRUE(employee->getIsAvailable());
}

TEST_F(EmployeeTest, SettersWorkCorrectly) {
    ContactInfo newData("anna@work.com", "+78887776655", "СПб, Невский 22");
    tm newBirth = {};
    newBirth.tm_year = 1985 - 1900;
    newBirth.tm_mon = 10;
    newBirth.tm_mday = 25;
    time_t newBirthDate = mktime(&newBirth);

    employee->setName("Екатерина");
    employee->setSurname("Павлова");
    employee->setBirthDate(newBirthDate);
    employee->setContactInfo(newData);
    employee->setSalary(88000.0);
    employee->setIsAvailable(false);

    EXPECT_EQ(employee->getName(), "Екатерина");
    EXPECT_EQ(employee->getSurname(), "Павлова");
    EXPECT_EQ(employee->getBirthDate(), newBirthDate);
    EXPECT_EQ(employee->getContactInfo().getEmail(), "anna@work.com");
    EXPECT_EQ(employee->getContactInfo().getPhone(), "+78887776655");
    EXPECT_EQ(employee->getContactInfo().getAddress(), "СПб, Невский 22");
    EXPECT_DOUBLE_EQ(employee->getSalary(), 88000.0);
    EXPECT_FALSE(employee->getIsAvailable());
}

TEST_F(EmployeeTest, MarkUnavailableSetsAvailabilityToFalse) {
    EXPECT_TRUE(employee->getIsAvailable());

    employee->markUnavailable();

    EXPECT_FALSE(employee->getIsAvailable());
}

TEST_F(EmployeeTest, AvailabilityCanBeToggledManually) {
    employee->setIsAvailable(false);
    EXPECT_FALSE(employee->getIsAvailable());

    employee->setIsAvailable(true);
    EXPECT_TRUE(employee->getIsAvailable());
}

TEST_F(EmployeeTest, FullNameAndAgeWorkFromBaseClass) {
    string fullName = employee->getFullName();
    EXPECT_EQ(fullName, "Анна Смирнова");

    int age = employee->getAge();
    EXPECT_GT(age, 0);
    EXPECT_LT(age, 100);
}
