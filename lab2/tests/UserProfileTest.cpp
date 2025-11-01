#include <gtest/gtest.h>
#include "UserProfile.h"

using namespace std;

class UserProfileTest : public ::testing::Test {
protected:
    void SetUp() override {
        interests = { "reading", "gaming", "travel" };
        user = new UserProfile("Ivan", "Petrov", "1995-05-12", "2020-01-01",
            "+71234567890", "Russia", "Moscow", interests);
    }

    void TearDown() override {
        delete user;
    }

    UserProfile* user;
    vector<string> interests;
};

TEST_F(UserProfileTest, GettersReturnCorrectValues) {
    EXPECT_EQ(user->getFirstName(), "Ivan");
    EXPECT_EQ(user->getLastName(), "Petrov");
    EXPECT_EQ(user->getBirthDate(), "1995-05-12");
    EXPECT_EQ(user->getRegistrationDate(), "2020-01-01");
    EXPECT_EQ(user->getPhone(), "+71234567890");
    EXPECT_EQ(user->getCountry(), "Russia");
    EXPECT_EQ(user->getCity(), "Moscow");
    EXPECT_EQ(user->getInterests(), interests);
}

TEST_F(UserProfileTest, SettersChangeValues) {
    user->setFirstName("Sergey");
    user->setLastName("Ivanov");
    user->setBirthDate("1990-12-01");
    user->setRegistrationDate("2021-05-05");
    user->setPhone("+79876543210");
    user->setCountry("USA");
    user->setCity("New York");
    user->setInterests({ "music", "art" });

    EXPECT_EQ(user->getFirstName(), "Sergey");
    EXPECT_EQ(user->getLastName(), "Ivanov");
    EXPECT_EQ(user->getBirthDate(), "1990-12-01");
    EXPECT_EQ(user->getRegistrationDate(), "2021-05-05");
    EXPECT_EQ(user->getPhone(), "+79876543210");
    EXPECT_EQ(user->getCountry(), "USA");
    EXPECT_EQ(user->getCity(), "New York");

    vector<string> expectedInterests = { "music", "art" };
    EXPECT_EQ(user->getInterests(), expectedInterests);
}

TEST_F(UserProfileTest, UpdateProfileCopiesAllFields) {
    vector<string> newInterests = { "sports", "coding" };
    UserProfile newProfile("Oleg", "Smirnov", "1993-03-03", "2023-09-15",
        "+79999999999", "Germany", "Berlin", newInterests);

    testing::internal::CaptureStdout();
    user->updateProfile(newProfile);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(user->getFirstName(), "Oleg");
    EXPECT_EQ(user->getLastName(), "Smirnov");
    EXPECT_EQ(user->getBirthDate(), "1993-03-03");
    EXPECT_EQ(user->getRegistrationDate(), "2023-09-15");
    EXPECT_EQ(user->getPhone(), "+79999999999");
    EXPECT_EQ(user->getCountry(), "Germany");
    EXPECT_EQ(user->getCity(), "Berlin");
    EXPECT_EQ(user->getInterests(), newInterests);
}

TEST_F(UserProfileTest, PrintProfileInfoOutputsCorrectText) {
    testing::internal::CaptureStdout();
    user->printProfileInfo();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Имя и фамилия: Ivan Petrov"), string::npos);
    EXPECT_NE(output.find("Дата рождения: 1995-05-12"), string::npos);
    EXPECT_NE(output.find("Дата регистрации: 2020-01-01"), string::npos);
    EXPECT_NE(output.find("Телефон: +71234567890"), string::npos);
    EXPECT_NE(output.find("Страна: Russia"), string::npos);
    EXPECT_NE(output.find("Город: Moscow"), string::npos);
    EXPECT_NE(output.find("Интересы: reading, gaming, travel"), string::npos);
}
