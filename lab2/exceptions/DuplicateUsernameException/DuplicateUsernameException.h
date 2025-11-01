#pragma once
#include "Exception.h"

class DuplicateUsernameException : public Exception {
public:
    DuplicateUsernameException(const char* message);
};
