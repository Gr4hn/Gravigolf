#pragma once 
#include "Ball.hpp"
#include "Planet.hpp"
#include "Portal.hpp"
#include "Aim.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

enum class GameState {
    AIMING,
    SHOOTING,
    SCORED
};

class Game {
public:
    sf::RenderWindow window;
    GameState currentState;
    Ball ball;
    Aim aim;
    Portal goal;
    std::vector<Planet> planets;
    
    Game();

    void run();
private:
    void processEvents();
    void update(float deltatime);
    void render();
};