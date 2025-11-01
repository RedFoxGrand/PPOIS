#include <gtest/gtest.h>
#include "FeedbackForm.h"

class FeedbackFormTest : public ::testing::Test {
protected:
    FeedbackForm* feedback;
    time_t submissionDate;

    void SetUp() override {
        submissionDate = time(nullptr) - 3600;
        feedback = new FeedbackForm("Отличный сервис!", 5, submissionDate);
    }

    void TearDown() override {
        delete feedback;
    }
};

TEST_F(FeedbackFormTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(feedback->getReview(), "Отличный сервис!");
    EXPECT_EQ(feedback->getRating(), 5);
    EXPECT_EQ(feedback->getSubmissionDate(), submissionDate);
}

TEST_F(FeedbackFormTest, SettersWorkCorrectly) {
    time_t newDate = time(nullptr);
    feedback->setReview("Хорошо, но можно лучше");
    feedback->setRating(3);
    feedback->setSubmissionDate(newDate);

    EXPECT_EQ(feedback->getReview(), "Хорошо, но можно лучше");
    EXPECT_EQ(feedback->getRating(), 3);
    EXPECT_EQ(feedback->getSubmissionDate(), newDate);
}

TEST_F(FeedbackFormTest, ChangeReviewUpdatesReviewText) {
    string result = feedback->changeReview("Обслуживание стало хуже");
    EXPECT_EQ(result, "Обслуживание стало хуже");
    EXPECT_EQ(feedback->getReview(), "Обслуживание стало хуже");
}

TEST_F(FeedbackFormTest, IsPositiveReturnsTrueForHighRatings) {
    feedback->setRating(4);
    EXPECT_TRUE(feedback->isPositive());

    feedback->setRating(5);
    EXPECT_TRUE(feedback->isPositive());
}

TEST_F(FeedbackFormTest, IsPositiveReturnsFalseForLowRatings) {
    feedback->setRating(3);
    EXPECT_FALSE(feedback->isPositive());

    feedback->setRating(1);
    EXPECT_FALSE(feedback->isPositive());
}
