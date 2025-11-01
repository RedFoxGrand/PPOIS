#include "FeedbackForm.h"

FeedbackForm::FeedbackForm(const string& review, int rating, time_t submissionDate) : 
    review_(review), 
    rating_(rating), 
    submissionDate_(submissionDate) {
}

void FeedbackForm::setReview(const string& review) {
    review_ = review; 
}
void FeedbackForm::setRating(int rating) {
    rating_ = rating; 
}
void FeedbackForm::setSubmissionDate(time_t date) {
    submissionDate_ = date; 
}

const string& FeedbackForm::getReview() const {
    return review_; 
}
int FeedbackForm::getRating() const {
    return rating_; 
}
time_t FeedbackForm::getSubmissionDate() const { 
    return submissionDate_; 
}

string FeedbackForm::changeReview(const string& newReview) {
    review_ = newReview;
    return review_;
}

bool FeedbackForm::isPositive() const {
    return rating_ >= 4;
}