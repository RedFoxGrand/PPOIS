#pragma once
#include <exception>
#include <string>

using namespace std;

class Exception : public std::exception {
protected:
    string message_;
public:
    Exception(const char* message);
    Exception(const string& message);
    Exception(const Exception& other);

    const char* what() const noexcept override;
};
