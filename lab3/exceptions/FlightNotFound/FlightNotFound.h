#pragma once
#include "Exception.h"

class FlightNotFound : public Exception {
public:
    FlightNotFound(const char* message);
};