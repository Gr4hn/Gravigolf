#pragma once

struct Vector2D {
    float x, y;

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(float scalar) const;
    Vector2D operator/(float scalar) const;

    float length() const;
    float lengthSquared() const;
    Vector2D normalized() const;
    float dot(const Vector2D& other) const;
    float distance(const Vector2D& other) const;
};