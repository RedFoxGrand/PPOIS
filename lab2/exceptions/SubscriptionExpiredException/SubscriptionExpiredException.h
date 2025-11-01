#pragma once
#include "Exception.h"

class SubscriptionExpiredException : public Exception {
public:
    SubscriptionExpiredException(const char* message);
};
