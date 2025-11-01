#pragma once
#include "Exception.h"

class InvalidStatusException : public Exception {
public:
    InvalidStatusException(const char* message);
};