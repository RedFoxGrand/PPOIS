#pragma once
#include "Exception.h"

class PassengerNotFound : public Exception {
public:
    PassengerNotFound(const char* message);
};