#pragma once
#include "Exception.h"

class InvalidCapacityException : public Exception {
public:
    InvalidCapacityException(const char* message);
};