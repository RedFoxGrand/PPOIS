#include "Set.h"
#include <iostream>
#include <string>
#include <vector>

Set::SetElement::SetElement() : type(STRING) {}
Set::SetElement::SetElement(const string& str) : type(STRING), stringValue(str) {}
Set::SetElement::SetElement(const vector<SetElement>& set) : type(SET), setValue(set) {}

bool operator==(const Set::SetElement& A, const Set::SetElement& B) {
    if (A.type != B.type) return false;
    if (A.type == Set::STRING) return A.stringValue == B.stringValue;
    if (A.type == Set::SET) {
        Set tempA(A.setValue), tempB(B.setValue);
        return tempA == tempB;
    }
    return false;
}

Set::Set() {}

Set::Set(const string& str) {
    ParseFromString(str);
}

Set::Set(const vector<SetElement>& elements) : elements(elements) {
    RemoveDuplicates();
}

Set::Set(const Set& other) : elements(other.elements) {}

Set& Set::operator=(const Set& other) {
    if (this != &other) elements = other.elements;
    return *this;
}

bool Set::Contains(const SetElement& element) const {
    for (const auto& el : elements) if (el == element) return true;
    return false;
}

bool Set::EmptyCheck() const {
    return elements.empty();
}

size_t Set::Cardinality() const {
    return elements.size();
}

void Set::AddElement(const SetElement& element) {
    if (!Contains(element)) elements.push_back(element);
}

void Set::RemoveElement(const SetElement& element) {
    auto newEnd = remove_if(elements.begin(), elements.end(), [&element](const SetElement& currentElement) {
        return currentElement == element;
        });
    elements.erase(newEnd, elements.end());
}

Set Set::operator+(const Set& other) const {
    Set result(*this);
    for (const auto& element : other.elements) result.AddElement(element);
    return result;
}

Set& Set::operator+=(const Set& other) {
    for (const auto& element : other.elements) AddElement(element);
    return *this;
}

Set Set::operator*(const Set& other) const {
    Set result;
    for (const auto& element : elements) {
        if (other.Contains(element)) result.AddElement(element);
    }
    return result;
}

Set& Set::operator*=(const Set& other) {
    vector<SetElement> intersection;
    for (const auto& element : elements) {
        if (other.Contains(element)) intersection.push_back(element);
    }
    elements = intersection;
    return *this;
}

Set Set::operator-(const Set& other) const {
    Set result;
    for (const auto& element : elements) {
        if (!other.Contains(element)) result.AddElement(element);
    }
    return result;
}

Set& Set::operator-=(const Set& other) {
    elements.erase(
        remove_if(elements.begin(), elements.end(),
            [&other](const SetElement& element) { return other.Contains(element); }),
        elements.end()
    );
    return *this;
}

bool Set::operator==(const Set& other) const {
    if (elements.size() != other.elements.size()) return false;
    for (const auto& element : elements) {
        bool found = false;
        for (const auto& otherElement : other.elements) {
            if (element == otherElement) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }

    return true;
}

bool Set::operator!=(const Set& other) const {
    return !(*this == other);
}

bool Set::operator[](const SetElement& element) const {
    return Contains(element);
}

Set Set::PowerSet() const {
    Set result;
    result.AddElement(SetElement(vector<SetElement>()));

    size_t n = elements.size();
    size_t total = 1 << n;

    for (size_t i = 1; i < total; ++i) {
        vector<SetElement> subset;
        for (size_t j = 0; j < n; ++j) {
            if (i & (1 << j)) subset.push_back(elements[j]);
        }
        result.AddElement(SetElement(subset));
    }

    return result;
}

Set::SetElement Set::ParsingElement(const string& str, int& pos) const {
    while (pos < (int)str.size() && SpaceCheck(str[pos])) pos++;
    if (pos < (int)str.size() && str[pos] == '{') return ParsingSet(str, pos);

    string token;
    while (pos < (int)str.size() && str[pos] != ',' && str[pos] != '}' && !SpaceCheck(str[pos])) {
        if (str[pos] == '{' && !token.empty()) {
            throw invalid_argument("Неожиданнная '{' внутри токена");
        }
        token.push_back(str[pos]);
        pos++;
    }

    for (char ch : token) {
        if (!DigitCheck(ch) && !LetterCheck(ch) && ch != '_') {
            throw invalid_argument("Недопустимый символ: " + string(1, ch));
        }
    }

    return SetElement(token);
}

Set::SetElement Set::ParsingSet(const string& str, int& pos) const {
    if (str[pos] != '{') throw invalid_argument("Ожидалась '{'");

    SetElement result;
    result.type = SET;
    pos++;

    vector<SetElement> vec;
    while (pos < (int)str.size()) {
        while (pos < (int)str.size() && SpaceCheck(str[pos])) pos++;
        if (pos < (int)str.size() && str[pos] == '}') {
            pos++;
            break;
        }

        SetElement el = ParsingElement(str, pos);
        vec.push_back(el);

        while (pos < (int)str.size() && SpaceCheck(str[pos])) pos++;
        if (pos < (int)str.size() && str[pos] == ',') pos++;
    }
    result.setValue = vec;

    return result;
}

void Set::ParseFromString(const string& str) {
    elements.clear();
    string cleanStr = str;
    cleanStr.erase(remove_if(cleanStr.begin(), cleanStr.end(),
        [this](char c) { return SpaceCheck(c); }),
        cleanStr.end());

    if (cleanStr.empty() || cleanStr.front() != '{' || cleanStr.back() != '}') {
        throw invalid_argument("Недопустимый формат множества");
    }

    int pos = 0;
    SetElement result = ParsingSet(cleanStr, pos);
    elements = result.setValue;
    RemoveDuplicates();
}

void Set::RemoveDuplicates() {
    vector<SetElement> uniqueElements;
    for (const auto& element : elements) {
        bool found = false;
        for (const auto& uniq : uniqueElements) {
            if (uniq == element) {
                found = true;
                break;
            }
        }
        if (!found) uniqueElements.push_back(element);
    }
    elements = uniqueElements;
}

string Set::ElementToString(const SetElement& element) const {
    if (element.type == STRING) return element.stringValue;

    string result = "{";
    for (size_t i = 0; i < element.setValue.size(); i++) {
        result += ElementToString(element.setValue[i]);
        if (i < element.setValue.size() - 1) result += ", ";
    }
    result += "}";

    return result;
}

bool Set::SpaceCheck(char ch) const {
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
}

bool Set::DigitCheck(char ch) const {
    return (ch >= '0' && ch <= '9');
}

bool Set::LetterCheck(char ch) const {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

string Set::ToString() const {
    if (EmptyCheck()) return "{}";

    string result = "{";
    for (size_t i = 0; i < elements.size(); i++) {
        result += ElementToString(elements[i]);
        if (i < elements.size() - 1) result += ", ";
    }
    result += "}";

    return result;
}

Set Set::FromString(const string& str) {
    return Set(str);
}

ostream& operator<<(ostream& out, const Set& set) {
    out << set.ToString();
    return out;
}

istream& operator>>(istream& in, Set& set) {
    string str;
    getline(in, str);
    set = Set::FromString(str);
    return in;
}