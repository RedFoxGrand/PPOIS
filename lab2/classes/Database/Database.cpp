#include "Database.h"

Database::Database(bool isConnected, DatabaseType type, DatabaseConnectionType connectionType) :
    isConnected_(false),
    type_(type),
    connectionType_(connectionType) {
}

void Database::setIsConnected(bool isConnected) {
    isConnected_ = isConnected;
}

void Database::setType(DatabaseType type) {
    type_ = type;
}

void Database::setConnectionType(DatabaseConnectionType connectionType) {
    connectionType_ = connectionType;
}

bool Database::getIsConnected() const {
    return isConnected_;
}

DatabaseType Database::getType() const {
    return type_;
}

DatabaseConnectionType Database::getConnectionType() const {
    return connectionType_;
}

bool Database::connect() {
    if (isConnected_) throw DatabaseConnectionException("База данных уже подключена");

    isConnected_ = true;

    return true;
}

void Database::printType() const {
    switch (type_) {
    case DatabaseType::RELATIONAL: cout << "реляционная"; break;
    case DatabaseType::NON_RELATIONAL: cout << "нереляционная"; break;
    default: cout << "неизвестный"; break;
    }
    cout << endl;
}
