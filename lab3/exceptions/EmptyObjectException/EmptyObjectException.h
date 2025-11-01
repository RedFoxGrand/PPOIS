#pragma once
#include "Exception.h"

class EmptyObjectException : public Exception {
public:
    EmptyObjectException(const char* message);
};