#pragma once
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Vector2D.hpp"
#include <SFML/Graphics.hpp>

class Planet {
public: 
    Vector2D position;
    float radius;
    float mass;
    sf::Color color;

    Planet(Vector2D position, float radius, float mass, sf::Color color);

    Vector2D calculateGravity(const Vector2D & ballPosition) const;
    bool contains(const Vector2D& point) const;
    void render(sf::RenderWindow& window);
};