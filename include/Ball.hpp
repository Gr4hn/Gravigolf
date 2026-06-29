#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2D.hpp"

class Ball {
public:
    Vector2D position;
    Vector2D velocity;

    float radius = 8.0f;
    bool isMoving = false;
    int strokes = 0;

    void applyForce(Vector2D force);
    void update(float deltatime);
    void render(sf::RenderWindow& window);
    void shoot(Vector2D direction, float power);
    void reset(Vector2D startPos);
    bool isStopped() const;
};