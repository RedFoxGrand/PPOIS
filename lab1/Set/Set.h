#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Set {
public:
    enum ElementType { STRING, SET };

    struct SetElement {
        ElementType type;
        string stringValue;
        vector<SetElement> setValue;

        SetElement();
        SetElement(const string& str);
        SetElement(const vector<SetElement>& set);

        friend bool operator==(const SetElement& a, const SetElement& b);
    };

    Set();
    Set(const string& str);
    Set(const vector<SetElement>& elements);
    Set(const Set& other);

    Set& operator=(const Set& other);

    bool Contains(const SetElement& element) const;
    bool EmptyCheck() const;
    size_t Cardinality() const;
    void AddElement(const SetElement& element);
    void RemoveElement(const SetElement& element);

    Set operator+(const Set& other) const;
    Set& operator+=(const Set& other);
    Set operator*(const Set& other) const;
    Set& operator*=(const Set& other);
    Set operator-(const Set& other) const;
    Set& operator-=(const Set& other);
    bool operator==(const Set& other) const;
    bool operator!=(const Set& other) const;
    bool operator[](const SetElement& element) const;

    Set PowerSet() const;

    string ToString() const;
    static Set FromString(const std::string& str);

    friend ostream& operator<<(ostream& out, const Set& set);
    friend istream& operator>>(istream& in, Set& set);

private:
    vector<SetElement> elements;

    SetElement ParsingElement(const string& str, int& pos) const;
    SetElement ParsingSet(const string& str, int& pos) const;
    void ParseFromString(const string& str);

    void RemoveDuplicates();
    string ElementToString(const SetElement& element) const;
    bool SpaceCheck(char ch) const;
    bool DigitCheck(char ch) const;
    bool LetterCheck(char ch) const;
};