#include "header.h"

using namespace std;

Vector::Vector(double a, double b) : x(a), y(b) {}

Vector::Vector(const Vector& v) : x(v.x), y(v.y) {}

Vector::~Vector() {}

Vector operator~(const Vector& v) {
    return Vector(-v.x, -v.y);
}

Vector operator+(const Vector& v1, const Vector& v2) {
    return Vector(v1.x + v2.x, v1.y + v2.y);
}

Vector operator-(const Vector& v1, const Vector& v2) {
    return Vector(v1.x - v2.x, v1.y - v2.y);
}

double operator*(const Vector& v1, const Vector& v2) {
    return(v1.x * v2.x + v1.y * v2.y);
}

Vector operator*(const Vector& v1, double a) {
    return Vector(v1.x * a, v1.y *a );
}

Vector& Vector::operator++() {
    ++x;
    ++y;
    return *this;
}

Vector& Vector::operator++(int) {
    Vector temp = *this;
    ++x;
    ++y;
    return temp;
}

Vector& Vector::operator--() {
    --x;
    --y;
    return *this;
}

Vector& Vector::operator--(int) {
    Vector temp = *this;
    --x;
    --y;
    return temp;
}

Vector Vector::operator=(const Vector& v) {
    this->x = v.x;
    this->y = v.y;
    return Vector(x, y);
}

bool Vector::operator==(const Vector& v) {
    return (this->x == v.x && this->y == v.y);
}

bool Vector::operator!=(const Vector& v) {
    return(this->x != v.x || this->y != v.y);
}

ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(" << v.x << "," << v.y << ")";
    return os;
}

istream& operator>>(std::istream& is, Vector& v) {
    is >> v.x >> v.y;
    return is;
}

Container::Container() : size(0) {

    arr = new Vector[MAX_SIZE];
}

Container::~Container() {
    delete[] arr;
}

void Container::addToContainer(const Vector& v) {
    if (size > MAX_SIZE) throw std::overflow_error("Переполнение массива");
    arr[size++] = v;
}

const Vector& Container::operator[](int index) const {
    if (index < 0 || index > MAX_SIZE) throw std::out_of_range("Некорректный индекс массива");
    return arr[index];
}
