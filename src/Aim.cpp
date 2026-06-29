#include "Aim.hpp"
#include "Ball.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Mouse.hpp"
#include "Vector2D.hpp"

void Aim::handleInput(const sf::Event& event, const sf::RenderWindow& window, Ball& ball) {
    if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {

        if (mousePressed->button == sf::Mouse::Button::Left && ball.isStopped()) {
            isAming = true;
        } 
    }

    if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>()) {
        if (isAming == true) {
            currentMousePosition.x = static_cast<float>(mouseMoved->position.x);
            currentMousePosition.y = static_cast<float>(mouseMoved->position.y);
        }
    }


    if (const auto* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (mouseReleased->button == sf::Mouse::Button::Left && isAming == true) {
            Vector2D dragVector = ball.position - currentMousePosition;
            float power = dragVector.length();
            if (power > maxPower) {
                power = maxPower;
            }
            ball.shoot(dragVector, power);
            isAming = false;
        }
    }
}

void Aim::render(sf::RenderWindow& window, const Ball& ball) const {
    if (isAming == true) {
        Vector2D dragVector = ball.position - currentMousePosition;
        float power = dragVector.length();
        if (power > maxPower) {
            power = maxPower;
            dragVector = dragVector.normalized() * maxPower;
        }
        sf::Color lineColor = sf::Color::White;
        if (power > maxPower * 0.7f){
            lineColor = sf::Color::Yellow;
        }
        if (power > maxPower * 0.9f) {
            lineColor = sf::Color::Red;
        }
        sf::Vertex line[] = {
            sf::Vertex{sf::Vector2f(ball.position.x, ball.position.y), lineColor},
            sf::Vertex{sf::Vector2f(ball.position.x + dragVector.x, ball.position.y + dragVector.y), lineColor}
        };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    
    }
}