#pragma once
#include "Exception.h"

class InvadRateException : public Exception {
public:
    InvadRateException(const char* message);
};