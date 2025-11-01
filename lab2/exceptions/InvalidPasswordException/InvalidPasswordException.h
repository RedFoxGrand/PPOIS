#pragma once
#include "Exception.h"

class InvalidPasswordException : public Exception {
public:
    InvalidPasswordException(const char* message);
};
