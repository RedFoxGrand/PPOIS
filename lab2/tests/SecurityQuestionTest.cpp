#include <gtest/gtest.h>
#include "SecurityQuestion.h"

using namespace std;

class SecurityQuestionTest : public ::testing::Test {
protected:
    void SetUp() override {
        question = new SecurityQuestion("Как зовут вашего первого питомца?", "Бобик");
    }

    void TearDown() override {
        delete question;
    }

    SecurityQuestion* question;
};

TEST_F(SecurityQuestionTest, GettersReturnCorrectValues) {
    EXPECT_EQ(question->getQuestion(), "Как зовут вашего первого питомца?");
    EXPECT_EQ(question->getAnswer(), "Бобик");
}

TEST_F(SecurityQuestionTest, SettersChangeValues) {
    question->setQuestion("В каком городе вы родились?");
    question->setAnswer("Москва");

    EXPECT_EQ(question->getQuestion(), "В каком городе вы родились?");
    EXPECT_EQ(question->getAnswer(), "Москва");
}

TEST_F(SecurityQuestionTest, VerifyAnswerCorrect) {
    testing::internal::CaptureStdout();
    bool result = question->verifyAnswer("Бобик");
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(result);
}

TEST_F(SecurityQuestionTest, VerifyAnswerIncorrect) {
    testing::internal::CaptureStdout();
    bool result = question->verifyAnswer("Шарик");
    string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(result);
}

TEST_F(SecurityQuestionTest, VerifyAnswerCaseSensitive) {
    testing::internal::CaptureStdout();
    bool result = question->verifyAnswer("бобик");
    string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(result);
}
