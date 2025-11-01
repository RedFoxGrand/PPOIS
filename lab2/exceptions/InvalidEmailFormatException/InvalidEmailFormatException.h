#pragma once
#include "Exception.h"

class InvalidEmailFormatException : public Exception {
public:
    InvalidEmailFormatException(const char* message);
};
