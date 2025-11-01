#include "SecurityQuestion.h"

SecurityQuestion::SecurityQuestion(const string& question, const string& answer) :
    question_(question),
    answer_(answer) {}

void SecurityQuestion::setQuestion(const string& question) {
    question_ = question;
}
void SecurityQuestion::setAnswer(const string& answer) {
    answer_ = answer;
}

const string& SecurityQuestion::getQuestion() const {
    return question_;
}
const string& SecurityQuestion::getAnswer() const {
    return answer_;
}

bool SecurityQuestion::verifyAnswer(const string& userAnswer) {
    return userAnswer == answer_;
}
