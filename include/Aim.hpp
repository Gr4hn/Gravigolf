#pragma once

#include <SFML/Graphics.hpp>
#include "SFML/Graphics/RenderWindow.hpp"
#include "Vector2D.hpp"
#include "Ball.hpp"

class Aim {
public:
    bool isAming = false;
    Vector2D startMousePosition;
    Vector2D currentMousePosition;
    float maxPower = 1500.0f;

    void handleInput(const sf::Event& event, const sf::RenderWindow& window, Ball& ball);
    void render(sf::RenderWindow& window, const Ball& ball) const;
};  