#pragma once
#include "Exception.h"

class CardExpiredException : public Exception {
public:
    CardExpiredException(const char* message);
};
