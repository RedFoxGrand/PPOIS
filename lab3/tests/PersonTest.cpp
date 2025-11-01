#include <gtest/gtest.h>
#include "Person.h"

using namespace std;

class PersonTest : public ::testing::Test {
protected:
    Person* person;
    ContactInfo* contact;
    time_t birthDate;

    void SetUp() override {
        contact = new ContactInfo("user@mail.com", "+79991234567", "Москва, ул. Ленина, 10");

        tm birth = {};
        birth.tm_year = 2000 - 1900;
        birth.tm_mon = 0;
        birth.tm_mday = 1;
        birthDate = mktime(&birth);

        person = new Person("Иван", "Иванов", birthDate, *contact);
    }

    void TearDown() override {
        delete person;
        delete contact;
    }
};

TEST_F(PersonTest, ConstructorInitializesValuesCorrectly) {
    EXPECT_EQ(person->getName(), "Иван");
    EXPECT_EQ(person->getSurname(), "Иванов");
    EXPECT_EQ(person->getBirthDate(), birthDate);
    EXPECT_EQ(person->getContactInfo().getEmail(), "user@mail.com");
    EXPECT_EQ(person->getContactInfo().getPhone(), "+79991234567");
    EXPECT_EQ(person->getContactInfo().getAddress(), "Москва, ул. Ленина, 10");
}

TEST_F(PersonTest, SettersWorkCorrectly) {
    ContactInfo newData("test@domain.com", "+78887776655", "СПб, Невский 1");
    tm newBirth = {};
    newBirth.tm_year = 1995 - 1900;
    newBirth.tm_mon = 5;
    newBirth.tm_mday = 15;
    time_t newBirthDate = mktime(&newBirth);

    person->setName("Петр");
    person->setSurname("Петров");
    person->setBirthDate(newBirthDate);
    person->setContactInfo(newData);

    EXPECT_EQ(person->getName(), "Петр");
    EXPECT_EQ(person->getSurname(), "Петров");
    EXPECT_EQ(person->getBirthDate(), newBirthDate);
    EXPECT_EQ(person->getContactInfo().getEmail(), "test@domain.com");
    EXPECT_EQ(person->getContactInfo().getPhone(), "+78887776655");
    EXPECT_EQ(person->getContactInfo().getAddress(), "СПб, Невский 1");
}

TEST_F(PersonTest, GetFullNameReturnsCorrectValue) {
    EXPECT_EQ(person->getFullName(), "Иван Иванов");
}

TEST_F(PersonTest, GetAgeReturnsCorrectValue) {
    time_t now = time(nullptr);
    tm* nowTm = localtime(&now);
    int currentYear = nowTm->tm_year + 1900;

    int expectedAge = currentYear - 2000;
    if ((nowTm->tm_mon < 0) || (nowTm->tm_mon == 0 && nowTm->tm_mday < 1)) {
        expectedAge--;
    }

    int actualAge = person->getAge();
    EXPECT_NEAR(actualAge, expectedAge, 1);
}
