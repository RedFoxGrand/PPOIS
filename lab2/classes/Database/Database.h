#pragma once
#include "DatabaseConnectionException.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

enum class DatabaseType { RELATIONAL, NON_RELATIONAL };
enum class DatabaseConnectionType { LOCAL, REMOTE };

class Database {
public:
    Database(bool isConnected, DatabaseType type, DatabaseConnectionType connectionType);

    void setIsConnected(bool isConnected);
    void setType(DatabaseType type);
    void setConnectionType(DatabaseConnectionType connectionType);

    bool getIsConnected() const;
    DatabaseType getType() const;
    DatabaseConnectionType getConnectionType() const;

    bool connect();
    void printType() const;

private:
    bool isConnected_;
    DatabaseType type_;
    DatabaseConnectionType connectionType_;
};
