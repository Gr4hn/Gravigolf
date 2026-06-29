#include "Planet.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Vector2D.hpp"

Planet::Planet(Vector2D position, float radius, float mass, sf::Color color) {
    this->position = position;
    this->radius = radius;
    this->mass = mass;
    this->color = color;
}

Vector2D Planet::calculateGravity(const Vector2D& ballPosition) const {
    Vector2D direction = position - ballPosition;
    float distanceSquared = direction.lengthSquared();

    float minimumDistance = radius + 10.0f;
    if (distanceSquared < minimumDistance * minimumDistance) {
        distanceSquared = minimumDistance * minimumDistance;
    }

    float forceMagnitude = mass / distanceSquared;
    return direction.normalized() * forceMagnitude;
}

bool Planet::contains(const Vector2D & point) const {
    return 0;
}

void Planet::render(sf::RenderWindow& window) {
    sf::CircleShape shape(radius);
    shape.setOrigin({radius, radius});
    shape.setPosition({position.x, position.y});
    shape.setFillColor(color);
    window.draw(shape);
}
