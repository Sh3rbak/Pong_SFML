#include <SFML/Graphics.hpp>

const int SCREEN_HEIGHT = 720;
const int SCREEN_WIGHT = 1240;
const float PLATFORM_HEIGHT = 100.f;
const float PLATFORM_WIGHT = 20.f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIGHT, SCREEN_HEIGHT), "P.O.N.G!");
    sf::RectangleShape leftPlatform(sf::Vector2f(PLATFORM_WIGHT, PLATFORM_HEIGHT));
    leftPlatform.setFillColor(sf::Color::White);
    leftPlatform.setPosition(SCREEN_WIGHT / 2.f, SCREEN_HEIGHT / 2.f);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(leftPlatform);
        window.display();
    }

    return 0;
}