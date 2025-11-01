#pragma once
#include "Exception.h"

class PassengerHistoryNotFound : public Exception {
public:
    PassengerHistoryNotFound(const char* message);
};