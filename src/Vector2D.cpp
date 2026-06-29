#include "Vector2D.hpp"
#include <cmath>

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D{x + other.x, y + other.y};
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D{x - other.x, y - other.y};
}

Vector2D Vector2D::operator*(float scalar) const {
    return Vector2D{x * scalar, y * scalar};
}

Vector2D Vector2D::operator/(float scalar) const {
    return Vector2D{x / scalar, y / scalar};
}

float Vector2D::length() const {
    return std::sqrt(x * x + y * y);
}

float Vector2D::lengthSquared() const {
    return x * x + y * y;
}

Vector2D Vector2D::normalized() const {
    float len = length();
    if (len != 0.0f) {
        return Vector2D{x / len, y / len};
    }
    return Vector2D{0.0f, 0.0f};
}

float Vector2D::dot(const Vector2D& other) const {
    return x * other.x + y * other.y;
}

float Vector2D::distance(const Vector2D& other) const {
    float dx = x - other.x;
    float dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}
