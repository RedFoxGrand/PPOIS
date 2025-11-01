#pragma once
#include "Exception.h"

class ExpiredException : public Exception {
public:
    ExpiredException(const char* message);
};