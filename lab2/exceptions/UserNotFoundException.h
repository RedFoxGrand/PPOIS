#pragma once
#include "Exception.h"

class UserNotFoundException : public Exception {
public:
    UserNotFoundException(const char* message);
};
