#pragma once
#include "Exception.h"

class InvalidFuelException : public Exception {
public:
    InvalidFuelException(const char* message);
};