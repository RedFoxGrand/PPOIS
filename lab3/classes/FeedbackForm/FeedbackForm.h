#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

class FeedbackForm {
public:
    FeedbackForm(const string& review, int rating, time_t submissionDate);

    void setReview(const string& review);
    void setRating(int rating);
    void setSubmissionDate(time_t date);

    const string& getReview() const;
    int getRating() const;
    time_t getSubmissionDate() const;

    string changeReview(const string& newReview);
    bool isPositive() const;

private:
    string review_;
    int rating_;
    time_t submissionDate_;
};
