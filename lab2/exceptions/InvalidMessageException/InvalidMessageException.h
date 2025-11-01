#pragma once
#include "Exception.h"

class InvalidMessageException : public Exception {
public:
    InvalidMessageException(const char* message);
};
