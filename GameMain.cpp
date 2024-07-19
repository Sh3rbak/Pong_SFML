#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace PongGame;

int main()
{
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDHT, SCREEN_HEIGHT), "P.O.N.G!");

    PongGame::Game* game = new PongGame::Game();
    InitGame(*game);

    sf::Clock game_lock;
    sf::Time lastTime = game_lock.getElapsedTime();

    while (window.isOpen())
    {
        HandleWindowEvents(*game, window);

        if (!window.isOpen())
        {
            break;
        }

        sf::Time currectTime = game_lock.getElapsedTime();
        float deltaTime = currectTime.asSeconds() - lastTime.asSeconds();
        lastTime = currectTime;

        UpdateGame(*game, deltaTime);

        window.clear();
        DrawGame(*game, window);
        window.display();
    }


    delete game;
    game = nullptr;

    return 0;
}