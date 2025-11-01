#pragma once
#include "Exception.h"

class DatabaseConnectionException : public Exception {
public:
    DatabaseConnectionException(const char* message);
};
