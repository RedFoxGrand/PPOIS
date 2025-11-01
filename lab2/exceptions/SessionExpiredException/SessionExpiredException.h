#pragma once
#include "Exception.h"

class SessionExpiredException : public Exception {
public:
    SessionExpiredException(const char* message);
};
