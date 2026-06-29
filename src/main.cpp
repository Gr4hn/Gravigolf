#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Clock.hpp"
#include <SFML/Graphics.hpp>
#include <Vector2D.hpp>
#include <Ball.hpp>
#include <Planet.hpp>
#include <Portal.hpp>
#include <Aim.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({1920u, 1080u}), "Gravigolf");
    window.setFramerateLimit(60);

    Ball myBall;
    Planet sun(Vector2D{960.0f, 540.0f}, 100.0f, 0.0f, sf::Color::Yellow);
    Planet mars(Vector2D{1200.0f, 900.0f}, 60.0f, 0.0f, sf::Color::Blue);
    Portal goal(Vector2D{800.0f, 400.0f}, 50.0f, sf::Color::Green);
    sf::Clock clock;

    Aim playerAim;
    myBall.reset(Vector2D{200.0f, 200.0f});

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            playerAim.handleInput(*event, window, myBall);
        }
        float deltatime = clock.restart().asSeconds();
        Vector2D gravityForce = sun.calculateGravity(myBall.position);
        myBall.applyForce(gravityForce);
        

        myBall.update(deltatime);
        goal.update(deltatime);
        if (goal.checkCapture(myBall)) {
            std::cout << "GOAAAAL!" << std::endl;
            myBall.reset(Vector2D{200.0f, 200.0f});
        }

        // Studsa mot höger och vänster vägg (X-axeln)
        if (myBall.position.x > 1920.0f || myBall.position.x < 0.0f) {
            myBall.velocity.x = -myBall.velocity.x;
        }
        // Studsa mot tak och golv (Y-axeln)
        if (myBall.position.y > 1080.0f || myBall.position.y < 0.0f) {
            myBall.velocity.y = -myBall.velocity.y;
        }

        window.clear(sf::Color(10, 10, 30));
        goal.render(window);
        sun.render(window);
        mars.render(window);
        myBall.render(window);
        playerAim.render(window, myBall);
        window.display();
    }
    
    return 0;
}