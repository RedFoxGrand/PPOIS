#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Vector {
public:
    Vector();
    Vector(double xBegValue, double yBegValue, double zBegValue, double xEndValue, double yEndValue, double zEndValue);
    Vector(const Vector& other);

    void SetCoordinatesBeg(double xBeg, double yBeg, double zBeg);
    void SetCoordinatesEnd(double xEnd, double yEnd, double zEnd);
    double GetXBeg() const;
    double GetYBeg() const;
    double GetZBeg() const;
    double GetXEnd() const;
    double GetYEnd() const;
    double GetZEnd() const;
    double LengthCalculate() const;

    Vector& operator=(const Vector& other);
    Vector operator+(const Vector& other) const;
    Vector operator+=(const Vector& other);
    Vector operator-(const Vector& other) const;
    Vector operator-=(const Vector& other);
    double operator*(const Vector& other) const;
    Vector operator%(const Vector& other) const;
    Vector operator*(double number) const;
    Vector operator*=(double number);
    Vector operator/(double number) const;
    Vector operator/=(double number);
    double operator^(const Vector& other) const;

    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
    bool operator<(const Vector& other) const;
    bool operator<=(const Vector& other) const;
    bool operator>(const Vector& other) const;
    bool operator>=(const Vector& other) const;

    friend ostream& operator<<(ostream& out, const Vector& vec);
    friend istream& operator>>(istream& in, Vector& vec);

private:
    double xBeg, yBeg, zBeg, xEnd, yEnd, zEnd;
};
