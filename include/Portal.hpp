#pragma once
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Vector2D.hpp"
#include "SFML/Graphics.hpp"
#include "Ball.hpp"


class Portal {
public:
    Vector2D position;
    float baseRadius;
    sf::Color color;
    float timePassed = 0.0f;

    Portal(Vector2D position, float radius, sf::Color color);
    bool checkCapture(const Ball& ball) const;
    void render(sf::RenderWindow& window) const;
    void update(float deltaTime);
};