#pragma once
#include "Exception.h"

class InvalidException : public Exception {
public:
    InvalidException(const char* message);
};