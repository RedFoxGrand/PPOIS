#include "Exception.h"

Exception::Exception(const char* message) : message_(message) {}
Exception::Exception(const std::string& message) : message_(message) {}
Exception::Exception(const Exception& other) : message_(other.message_) {}

const char* Exception::what() const noexcept {
    return message_.c_str();
}
