#include <gtest/gtest.h>
#include "ContactInfo.h"

using namespace std;

class ContactInfoTest : public ::testing::Test {
protected:
    ContactInfo* contact;

    void SetUp() override {
        contact = new ContactInfo("user@example.com", "+79998887766", "Москва, ул. Ленина, 1");
    }

    void TearDown() override {
        delete contact;
    }
};

TEST_F(ContactInfoTest, ConstructorInitializesValuesCorrectly) {
    EXPECT_EQ(contact->getEmail(), "user@example.com");
    EXPECT_EQ(contact->getPhone(), "+79998887766");
    EXPECT_EQ(contact->getAddress(), "Москва, ул. Ленина, 1");
}

TEST_F(ContactInfoTest, SettersWorkCorrectly) {
    contact->setEmail("new@mail.ru");
    contact->setPhone("+78887776655");
    contact->setAddress("Санкт-Петербург, Невский 10");

    EXPECT_EQ(contact->getEmail(), "new@mail.ru");
    EXPECT_EQ(contact->getPhone(), "+78887776655");
    EXPECT_EQ(contact->getAddress(), "Санкт-Петербург, Невский 10");
}

TEST_F(ContactInfoTest, ChangeEmailReturnsOldEmailAndUpdatesValue) {
    string oldEmail = contact->changeEmail("another@example.com");

    EXPECT_EQ(oldEmail, "user@example.com");
    EXPECT_EQ(contact->getEmail(), "another@example.com");
}

TEST_F(ContactInfoTest, ChangeEmailDoesNotChangeForInvalidAddress) {
    string oldEmail = contact->getEmail();

    string result = contact->changeEmail("invalid-email");

    EXPECT_EQ(result, oldEmail);               
    EXPECT_EQ(contact->getEmail(), oldEmail); 
}

TEST_F(ContactInfoTest, ChangeEmailWorksForValidComplexAddress) {
    string oldEmail = contact->getEmail();
    string newEmail = "john.doe@company.co.uk";

    string result = contact->changeEmail(newEmail);

    EXPECT_EQ(result, oldEmail);
    EXPECT_EQ(contact->getEmail(), newEmail);
}
