#pragma once
#include "Exception.h"

class InvalidAmountException : public Exception {
public:
    InvalidAmountException(const char* message);
};