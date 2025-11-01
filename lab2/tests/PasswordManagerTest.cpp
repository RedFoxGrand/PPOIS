#include <gtest/gtest.h>
#include "PasswordManager.h"
#include "Exception.h"

using namespace std;

class PasswordManagerTest : public ::testing::Test {
protected:
    PasswordManager* manager; vector<string> history;

    void SetUp() override {
        history = { "pass1", "pass2", "currentPass" };
        manager = new PasswordManager(true, false, history);
    }

    void TearDown() override {
        delete manager;
    }
};

TEST_F(PasswordManagerTest, GettersReturnCorrectValues) {
    EXPECT_TRUE(manager->isAutofillEnabled());
    EXPECT_FALSE(manager->isPasswordVisible());
    EXPECT_EQ(manager->getPasswordHistory(), history);
}

TEST_F(PasswordManagerTest, SettersUpdateValues) {
    manager->setAutofill(false);
    manager->setShowPassword(true);
    vector<string> newHistory = { "123", "456" };
    manager->setPasswordHistory(newHistory);

    EXPECT_FALSE(manager->isAutofillEnabled());
    EXPECT_TRUE(manager->isPasswordVisible());
    EXPECT_EQ(manager->getPasswordHistory(), newHistory);
}

TEST_F(PasswordManagerTest, VerifyPasswordSuccess) {
    testing::internal::CaptureStdout();
    bool result = manager->verifyPassword("currentPass");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
}

TEST_F(PasswordManagerTest, VerifyPasswordFailure) {
    testing::internal::CaptureStdout();
    bool result = manager->verifyPassword("wrongPass");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST(PasswordManagerEmptyHistoryTest, VerifyPasswordEmptyHistory) {
    PasswordManager pm(true, false, {});
    testing::internal::CaptureStdout();
    bool result = pm.verifyPassword("any");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
}

TEST_F(PasswordManagerTest, ChangePasswordSuccess) {
    testing::internal::CaptureStdout();
    manager->changePassword("newSecret123");
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(manager->getPasswordHistory().back(), "newSecret123");
}

TEST_F(PasswordManagerTest, ChangePasswordEmptyThrows) {
    EXPECT_THROW(manager->changePassword(""), InvalidPasswordException);
}

TEST_F(PasswordManagerTest, ChangePasswordDuplicateThrows) {
    EXPECT_THROW(manager->changePassword("currentPass"), InvalidPasswordException);
}

TEST_F(PasswordManagerTest, ResetPasswordSuccess) {
    testing::internal::CaptureStdout();
    manager->resetPassword("user@mail.com");
    string output = testing::internal::GetCapturedStdout();
}

TEST_F(PasswordManagerTest, ResetPasswordEmptyThrows) {
    EXPECT_THROW(manager->resetPassword(""), InvalidEmailFormatException);
}

TEST_F(PasswordManagerTest, ResetPasswordInvalidFormatThrows) {
    EXPECT_THROW(manager->resetPassword("user_mail_com"), InvalidEmailFormatException);
}
