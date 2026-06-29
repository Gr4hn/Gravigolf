#include "Portal.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Vector2D.hpp"
#include "cmath"
#include <cmath>

Portal::Portal(Vector2D position, float radius, sf::Color color) {
    this->position = position;
    this->baseRadius = radius;
    this->color = color;
}

void Portal::update(float deltaTime) {
    timePassed = timePassed + deltaTime;    
}

void Portal::render(sf::RenderWindow& window) const {
    float currentRadius = baseRadius + std::sin(timePassed * 5.0f) * 5.0f;
    sf::CircleShape shape(currentRadius);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(3.0f);
    shape.setOutlineColor(color);
    shape.setOrigin({currentRadius, currentRadius});
    shape.setPosition({position.x, position.y});
    window.draw(shape);
}

bool Portal::checkCapture(const Ball& ball) const {
    float distance = position.distance(ball.position);
    if (distance < baseRadius && ball.velocity.length() < 2000.0f) {
        return true;
    } else {
        return false;
    }
}
