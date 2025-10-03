#include "Vector.h"
#include <iostream>
#include <cmath>

Vector::Vector() : xBeg(0), yBeg(0), zBeg(0), xEnd(0), yEnd(0), zEnd(0) {}

Vector::Vector(double xBegValue, double yBegValue, double zBegValue, double xEndValue, double yEndValue, double zEndValue) :
    xBeg(xBegValue), yBeg(yBegValue), zBeg(zBegValue), xEnd(xEndValue), yEnd(yEndValue), zEnd(zEndValue) {}

Vector::Vector(const Vector& other) :
    xBeg(other.xBeg), yBeg(other.yBeg), zBeg(other.zBeg),
    xEnd(other.xEnd), yEnd(other.yEnd), zEnd(other.zEnd) {}

void Vector::SetСoordinatesBeg(double xBeg, double yBeg, double zBeg) {
    this->xBeg = xBeg;
    this->yBeg = yBeg;
    this->zBeg = zBeg;
}

void Vector::SetСoordinatesEnd(double xEnd, double yEnd, double zEnd) {
    this->xEnd = xEnd;
    this->yEnd = yEnd;
    this->zEnd = zEnd;
}

double Vector::GetXBeg() const { return xBeg; }
double Vector::GetYBeg() const { return yBeg; }
double Vector::GetZBeg() const { return zBeg; }
double Vector::GetXEnd() const { return xEnd; }
double Vector::GetYEnd() const { return yEnd; }
double Vector::GetZEnd() const { return zEnd; }

void Vector::Input() {
    std::cout << "Введите координаты начала вектора (x y z): ";
    std::cin >> xBeg >> yBeg >> zBeg;
    std::cout << "Введите координаты конца вектора (x y z): ";
    std::cin >> xEnd >> yEnd >> zEnd;
}

void Vector::DisplayMessege() const {
    std::cout << "Координаты начала вектора: (" << xBeg << ", " << yBeg << ", " << zBeg << ")\n";
    std::cout << "Координаты конца вектора:  (" << xEnd << ", " << yEnd << ", " << zEnd << ")\n";
}

double Vector::LengthCalculate() const {
    return sqrt(pow(xEnd - xBeg, 2) + pow(yEnd - yBeg, 2) + pow(zEnd - zBeg, 2));
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        xBeg = other.xBeg;
        yBeg = other.yBeg;
        zBeg = other.zBeg;
        xEnd = other.xEnd;
        yEnd = other.yEnd;
        zEnd = other.zEnd;
    }
    return *this;
}

Vector Vector::operator+(const Vector& other) const {
    return Vector(xBeg, yBeg, zBeg, xEnd + (other.xEnd - other.xBeg), yEnd + (other.yEnd - other.yBeg), zEnd + (other.zEnd - other.zBeg));
}

Vector Vector::operator+=(const Vector& other) {
    xEnd += (other.xEnd - other.xBeg);
    yEnd += (other.yEnd - other.yBeg);
    zEnd += (other.zEnd - other.zBeg);
    return *this;
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(xBeg, yBeg, zBeg, xEnd - (other.xEnd - other.xBeg), yEnd - (other.yEnd - other.yBeg), zEnd - (other.zEnd - other.zBeg));
}

Vector Vector::operator-=(const Vector& other) {
    xEnd -= (other.xEnd - other.xBeg);
    yEnd -= (other.yEnd - other.yBeg);
    zEnd -= (other.zEnd - other.zBeg);
    return *this;
}

double Vector::operator*(const Vector& other) const {
    double dx_this = xBeg - xEnd;
    double dy_this = yBeg - yEnd;
    double dz_this = zBeg - zEnd;
    double dx_other = other.xBeg - other.xEnd;
    double dy_other = other.yBeg - other.yEnd;
    double dz_other = other.zBeg - other.zEnd;

    return dx_this * dx_other + dy_this * dy_other + dz_this * dz_other;
}

Vector Vector::operator%(const Vector& other) const {
    double dx_this = xBeg - xEnd;
    double dy_this = yBeg - yEnd;
    double dz_this = zBeg - zEnd;
    double dx_other = other.xBeg - other.xEnd;
    double dy_other = other.yBeg - other.yEnd;
    double dz_other = other.zBeg - other.zEnd;

    double x_res = dy_this * dz_other - dz_this * dy_other;
    double y_res = dz_this * dx_other - dx_this * dz_other;
    double z_res = dx_this * dy_other - dy_this * dx_other;

    return Vector(0, 0, 0, x_res, y_res, z_res);
}

Vector Vector::operator*(double number) const {
    return Vector(xBeg, yBeg, zBeg, xBeg + number * (xEnd - xBeg), yBeg + number * (yEnd - yBeg), zBeg + number * (zEnd - zBeg));
}

Vector Vector::operator*=(double number) {
    xEnd = xBeg + number * (xEnd - xBeg);
    yEnd = yBeg + number * (yEnd - yBeg);
    zEnd = zBeg + number * (zEnd - zBeg);
    return *this;
}

Vector Vector::operator/(double number) const {
    if (number == 0) throw runtime_error("Ошибка! Делаение на ноль");
    return Vector(xBeg, yBeg, zBeg, xBeg + (xEnd - xBeg) / number, yBeg + (yEnd - yBeg) / number, zBeg + (zEnd - zBeg) / number);
}

Vector Vector::operator/=(double number) {
    if (number == 0) throw runtime_error("Ошибка! Делаение на ноль");
    xEnd = xBeg + (xEnd - xBeg) / number;
    yEnd = yBeg + (yEnd - yBeg) / number;
    zEnd = zBeg + (zEnd - zBeg) / number;
    return *this;
}

double Vector::operator^(const Vector& other) const {
    double lenght1 = this->LengthCalculate();
    double lenght2 = other.LengthCalculate();

    if (lenght1 == 0 || lenght2 == 0) throw runtime_error("Ошибка! Делаение на ноль");

    double cos = (*this * other) / (lenght1 * lenght2);
    return cos;
}

bool Vector::operator==(const Vector& other) const {
    return xBeg == other.xBeg && yBeg == other.yBeg && zBeg == other.zBeg && xEnd == other.xEnd && yEnd == other.yEnd && zEnd == other.zEnd;
}

bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

bool Vector::operator<(const Vector& other) const {
    return this->LengthCalculate() < other.LengthCalculate();
}

bool Vector::operator<=(const Vector& other) const {
    return this->LengthCalculate() <= other.LengthCalculate();
}

bool Vector::operator>(const Vector& other) const {
    return this->LengthCalculate() > other.LengthCalculate();
}

bool Vector::operator>=(const Vector& other) const {
    return this->LengthCalculate() >= other.LengthCalculate();
}

ostream& operator<<(ostream& out, const Vector& vec) {
    out << "Начало: (" << vec.xBeg << ", " << vec.yBeg << ", " << vec.zBeg << "), " << "Конец: (" << vec.xEnd << ", " << vec.yEnd << ", " << vec.zEnd << ")";
    return out;
}

istream& operator>>(istream& in, Vector& vec) {
    in >> vec.xBeg >> vec.yBeg >> vec.zBeg >> vec.xEnd >> vec.yEnd >> vec.zEnd;
    return in;
}