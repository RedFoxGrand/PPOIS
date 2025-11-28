#pragma once
#include <iostream>
#include <string>

using namespace std;

class Person {
public:
	Person() : name_(""), age_(0) {}
	Person(const string& name, const int age) : name_(name), age_(age) {}

	bool operator<(const Person& other) const {
		return age_ < other.age_ || (age_ == other.age_ && name_ < other.name_);
	}
	bool operator>(const Person& other) const {
		return age_ > other.age_ || (age_ == other.age_ && name_ > other.name_);
	}
	bool operator<=(const Person& other) const {
		return age_ <= other.age_ || (age_ == other.age_ && name_ <= other.name_);
	}
	bool operator>=(const Person& other) const {
		return age_ >= other.age_ || (age_ == other.age_ && name_ >= other.name_);
	}
	bool operator==(const Person& other) const {
		return age_ == other.age_ && name_ == other.name_;
	}
	bool operator!=(const Person& other) const {
		return age_ != other.age_ && name_ != other.name_;
	}
	friend ostream& operator<<(ostream& out, const Person& person) {
		return out << person.name_ << " (" << person.age_ << ")";
	}

private:
	string name_;
	int age_;
};