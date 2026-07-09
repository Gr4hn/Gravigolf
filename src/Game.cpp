#include "Game.hpp"
#include "Planet.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "Vector2D.hpp"
#include "iostream"

Game::Game()
    : window(sf::VideoMode({1920u, 1080u}), "Gravigolf"),
      goal(Vector2D{800.0f, 400.0f}, 50.0f, sf::Color::Green) {
  window.setFramerateLimit(60);
  currentState = GameState::AIMING;

  planets.push_back(
      Planet(Vector2D{960.0f, 540.0f}, 100.0f, 1000000.0f, sf::Color::Yellow));
  planets.push_back(
      Planet(Vector2D{1200.0f, 900.0f}, 60.0f, 1000000.0f, sf::Color::Blue));

  ball.reset(Vector2D{200.0f, 200.0f});
}

void Game::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    processEvents();
    float deltatime = clock.restart().asSeconds();
    update(deltatime);
    render();
  }
}

void Game::processEvents() {
  while (auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }
    if (currentState == GameState::AIMING) {
      aim.handleInput(*event, window, ball);
      if (ball.isStopped() == false) {
        currentState = GameState::SHOOTING;
      }
    }
  }
}

void Game::update(float deltatime) {
  if (currentState == GameState::SHOOTING) {
    for (Planet &planet : planets) {
      Vector2D force = planet.calculateGravity(ball.position);
      ball.applyForce(force);
    }
    ball.update(deltatime);
    if (ball.position.x > 1920.0f || ball.position.x < 0.0f) {
      ball.velocity.x = -ball.velocity.x;
    }
    if (ball.position.y > 1080.0f || ball.position.y < 0.0f) {
      ball.velocity.y = -ball.velocity.y;
    }

    for (Planet &planet : planets) {
      float distance = planet.position.distance(ball.position);
      if (distance <= planet.radius + ball.radius) {
        ball.velocity = Vector2D{0.0f, 0.0f};
        ball.isMoving = false;
        currentState = GameState::AIMING;
        break;
      }
    }
    goal.update(deltatime);
    if (goal.checkCapture(ball)) {
      std::cout << "GOAAAAL!" << std::endl;

      ball.reset(Vector2D{200.0f, 200.0f});

      currentState = GameState::AIMING;
    }
  }
}

void Game::render() {
  window.clear();
  for (Planet &planet : planets) {
    planet.render(window);
  }
  goal.render(window);
  ball.render(window);
  if (currentState == GameState::AIMING) {
    aim.render(window, ball, planets);
  }
  window.display();
}
