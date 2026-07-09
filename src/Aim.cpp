#include "Aim.hpp"
#include "Ball.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Mouse.hpp"
#include "Vector2D.hpp"

void Aim::handleInput(const sf::Event &event, const sf::RenderWindow &window,
                      Ball &ball) {
  if (const auto *mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {

    if (mousePressed->button == sf::Mouse::Button::Left && ball.isStopped()) {
      isAming = true;
    }
  }

  if (const auto *mouseMoved = event.getIf<sf::Event::MouseMoved>()) {
    if (isAming == true) {
      currentMousePosition.x = static_cast<float>(mouseMoved->position.x);
      currentMousePosition.y = static_cast<float>(mouseMoved->position.y);
    }
  }

  if (const auto *mouseReleased =
          event.getIf<sf::Event::MouseButtonReleased>()) {
    if (mouseReleased->button == sf::Mouse::Button::Left && isAming == true) {
      Vector2D dragVector = ball.position - currentMousePosition;
      float dragDistance = dragVector.length();
      float maxDrag = 300.0f;
      if (dragDistance > maxDrag) {
        dragDistance = maxDrag;
        dragVector = dragVector.normalized();
      }
      float power = dragDistance * 5.0f;
      ball.shoot(dragVector, power);
      isAming = false;
    }
  }
}

void Aim::render(sf::RenderWindow &window, const Ball &ball, const std::vector<Planet> &planets) const {
  if (isAming == true) {
    Vector2D dragVector = ball.position - currentMousePosition;
    float dragDistance = dragVector.length();
    float maxDrag = 300.0f;
    if (dragDistance > maxDrag) {
      dragDistance = maxDrag;
      dragVector = dragVector.normalized() * maxDrag;
    }

    float power = dragDistance * 5.0f;

    sf::Color lineColor = sf::Color::White;
    if (power > maxPower * 0.7f) {
      lineColor = sf::Color::Yellow;
    }
    if (power > maxPower * 0.9f) {
      lineColor = sf::Color::Red;
    }
    sf::VertexArray curve(sf::PrimitiveType::LineStrip);

    Vector2D simPos = ball.position;
    Vector2D simVel = dragVector.normalized() * power;
    float simDeltaTime = 0.016f;

    for (int i = 0; i < 50; i++) {
        curve.append(sf::Vertex{sf::Vector2f(simPos.x, simPos.y), lineColor});
        for (const Planet &planet : planets) {
            Vector2D force = planet.calculateGravity(simPos);
            simVel = simVel + force;
        }
        simPos = simPos + (simVel * simDeltaTime);
        simVel = simVel * 0.995f;

        bool hit = false;
            for (const Planet& planet : planets) {
                if (planet.position.distance(simPos) <= planet.radius + ball.radius) {
                    hit = true;
                    break;
                }
            }
        if (hit) break;
        if (simPos.x > 1920.0f || simPos.x < 0.0f) simVel.x = -simVel.x;
            if (simPos.y > 1080.0f || simPos.y < 0.0f) simVel.y = -simVel.y;
    }

    window.draw(curve);
  }
}