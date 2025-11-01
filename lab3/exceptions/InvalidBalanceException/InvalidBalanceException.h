#pragma once
#include "Exception.h"

class InvalidBalanceException : public Exception {
public:
    InvalidBalanceException(const char* message);
};