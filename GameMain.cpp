#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <random>

const int SCREEN_HEIGHT = 720;
const int SCREEN_WIGHT = 1240;
const float PLATFORM_HEIGHT = SCREEN_HEIGHT / 8.f;
const float PLATFORM_WIGHT = SCREEN_WIGHT / 80.f;
const float RADIUS_BALL = SCREEN_WIGHT / 100.f;

const float INITIAL_SPEED_PLATFORM = 150;
const float INITIAL_SPEED_BALL = 50;

enum class DirectionBall : std::uint8_t
{
    Right,
    Left
};

sf::Vector2f NormalizeVector(sf::Vector2f vector)
{
    float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    sf::Vector2f normalizeVector;
    normalizeVector.x = vector.x / magnitude;
    normalizeVector.y = vector.y / magnitude;
    return normalizeVector;
}

sf::Vector2f DirectionBallInStart()
{
    DirectionBall direction = static_cast<DirectionBall>(rand() % 2);
    float directionX;
    float directionY = rand() / static_cast<float>(RAND_MAX) * SCREEN_HEIGHT;
    if (direction == DirectionBall::Right)
    {
        directionX = SCREEN_WIGHT / 4.f;
    }
    else
    {
        directionX = -SCREEN_WIGHT / 4.f;
    }
    return NormalizeVector({ directionX, directionY });
}

int main()
{
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIGHT, SCREEN_HEIGHT), "P.O.N.G!");

    sf::RectangleShape separatorLine(sf::Vector2f(5.f, SCREEN_HEIGHT));
    separatorLine.setPosition(SCREEN_WIGHT / 2.f - 2.5f, 0);

    float lPlatformX = 20.f;
    float lPlatformY = SCREEN_HEIGHT / 2.f;
    sf::RectangleShape lPlatform(sf::Vector2f(PLATFORM_WIGHT, PLATFORM_HEIGHT));
    lPlatform.setFillColor(sf::Color::White);
    lPlatform.setOrigin(sf::Vector2f(PLATFORM_WIGHT / 2.f, PLATFORM_HEIGHT / 2.f));
    lPlatform.setPosition(lPlatformX, lPlatformY);

    float rPlatformX = SCREEN_WIGHT - 20.f;
    float rPlatformY = SCREEN_HEIGHT / 2.f;
    sf::RectangleShape rPlatform(sf::Vector2f(PLATFORM_WIGHT, PLATFORM_HEIGHT));
    rPlatform.setFillColor(sf::Color::White);
    rPlatform.setOrigin(sf::Vector2f(PLATFORM_WIGHT / 2.f, PLATFORM_HEIGHT / 2.f));
    rPlatform.setPosition(rPlatformX, rPlatformY);

    float ballX = SCREEN_WIGHT / 2.f;
    float ballY = SCREEN_HEIGHT / 2.f;
    sf::Vector2f directionBall = DirectionBallInStart();
    sf::CircleShape ball(RADIUS_BALL);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(sf::Vector2f(RADIUS_BALL, RADIUS_BALL));
    ball.setPosition(ballX, ballY);
    
    sf::Clock game_lock;
    sf::Time lastTime = game_lock.getElapsedTime();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time currectTime = game_lock.getElapsedTime();
        float deltaTime = currectTime.asSeconds() - lastTime.asSeconds();
        lastTime = currectTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (lPlatformY - PLATFORM_HEIGHT / 2) > 0)
        {
            lPlatformY -= INITIAL_SPEED_PLATFORM * deltaTime;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (lPlatformY + PLATFORM_HEIGHT / 2) < SCREEN_HEIGHT)
        {
            lPlatformY += INITIAL_SPEED_PLATFORM * deltaTime;
        }

        ball.setPosition(ball.getPosition() + directionBall * deltaTime * INITIAL_SPEED_BALL);

        lPlatform.setPosition(lPlatformX, lPlatformY);
        window.clear();
        window.draw(separatorLine);
        window.draw(lPlatform);
        window.draw(rPlatform);
        window.draw(ball);
        window.display();
    }

    return 0;
}