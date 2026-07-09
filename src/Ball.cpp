#include "Ball.hpp"
#include "SFML/Graphics/CircleShape.hpp"

void Ball::applyForce(Vector2D force) {
    velocity = velocity + force;
}

void Ball::update(float deltatime) {
    position = position + (velocity * deltatime);
    velocity = velocity * 0.995f;
    if (velocity.length() < 10.0f) {
        velocity = {0.0f, 0.0f};
        isMoving = false;
    }
}

void Ball::render(sf::RenderWindow& window) {
    sf::CircleShape shape(radius);
    shape.setOrigin({radius, radius});
    shape.setPosition({position.x, position.y});
    shape.setFillColor(sf::Color::White);
    window.draw(shape);
}

void Ball::shoot(Vector2D direction, float power) {
    direction = direction.normalized();
    velocity = direction * power;
    strokes ++;
    isMoving = true;
}

void Ball::reset(Vector2D startPos) {
    position = startPos;
    velocity = {0.0f, 0.0f};
    isMoving = false;
    strokes = 0;
}

bool Ball::isStopped() const{
    return !isMoving;
}