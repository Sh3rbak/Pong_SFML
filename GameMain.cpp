#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <random>
#include <cassert>

const std::string RESOURCES_PATH = "Assets/";

const int SCREEN_HEIGHT = 720;
const int SCREEN_WIDHT = 1240;
const float PLATFORM_HEIGHT = SCREEN_HEIGHT / 8.f;
const float PLATFORM_WIDHT = SCREEN_WIDHT / 100.f;
const float RADIUS_BALL = SCREEN_WIDHT / 120.f;

const float INITIAL_SPEED_PLATFORM = 250.f;
const float INITIAL_SPEED_BALL = 300.f;

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

sf::Vector2f GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
{
    sf::FloatRect textSize = text.getLocalBounds();
    return {
        (textSize.left + textSize.width) * relativePosition.x,
        (textSize.top + textSize.height) * relativePosition.y,
    };
}


sf::Vector2f DirectionBallInStart()
{
    DirectionBall direction = static_cast<DirectionBall>(rand() % 2);
    float directionX;
    float directionY = rand() / static_cast<float>(RAND_MAX) * SCREEN_HEIGHT;
    if (direction == DirectionBall::Right)
    {
        directionX = SCREEN_WIDHT / 4.f;
    }
    else
    {
        directionX = -SCREEN_WIDHT / 4.f;
    }
    return NormalizeVector({ directionX, directionY });
}

bool FindPlatformCollisionWithBall(const sf::RectangleShape& platform, const sf::CircleShape& ball)
{
    const float deltaX = abs(platform.getPosition().x - ball.getPosition().x);
    const float deltaY = abs(platform.getPosition().y - ball.getPosition().y);

    if (deltaX < PLATFORM_WIDHT / 2 + RADIUS_BALL && deltaY < PLATFORM_HEIGHT / 2 + RADIUS_BALL) 
    { 
        return true; 
    }

    if (deltaX <= PLATFORM_WIDHT / 2 && deltaY <= PLATFORM_HEIGHT / 2) 
    { 
        return true; 
    }

    const float cornerDelta = (deltaX - PLATFORM_WIDHT / 2) * (deltaX - PLATFORM_WIDHT / 2) +
        (deltaY - PLATFORM_HEIGHT / 2) * (deltaY - PLATFORM_HEIGHT / 2);

    return cornerDelta <= RADIUS_BALL * RADIUS_BALL;
}

enum class PartOfPlatform
{
    Top,
    Middle,
    Down
};

PartOfPlatform GetPartOfPlatformWithCollision(const sf::RectangleShape& platform, const sf::CircleShape& ball)
{
    const float deltaY = platform.getPosition().y - ball.getPosition().y;
    if (deltaY >= PLATFORM_HEIGHT / 6)
    {
        return PartOfPlatform::Top;
    }
    else if (deltaY <= -(PLATFORM_HEIGHT / 6))
    {
        return PartOfPlatform::Down;
    }
    return PartOfPlatform::Middle;
}

void SetDirectionInCaseOfCollisionWithPlatform(sf::Vector2f& direction, const PartOfPlatform& part)
{
    float sqrDirectionX = direction.x * direction.x;
    float sqrDirectionY = direction.y * direction.y;
    const float sqrDirection = sqrDirectionX + sqrDirectionY;

    if (part == PartOfPlatform::Top)
    {
        direction.y -= 0.3f;
    }
    if (part == PartOfPlatform::Down)
    {
        direction.y += .3f;
    }

    if (direction.y >= 0.9f)
    {
        direction.y = 0.9f;
    }
    else if (direction.y <= -0.9f)
    {
        direction.y = -0.9f;
    }

    sqrDirectionY = direction.y * direction.y;
    sqrDirectionX = abs(sqrDirection - sqrDirectionY);
    if (direction.x > 0)
    {
        direction.x = sqrt(sqrDirectionX) * -1.f;
    }
    else if (direction.x < 0)
    {
        direction.x = sqrt(sqrDirectionX);
    }
}

int main()
{
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDHT, SCREEN_HEIGHT), "P.O.N.G!");

    sf::RectangleShape separatorLine(sf::Vector2f(5.f, SCREEN_HEIGHT));
    separatorLine.setPosition(SCREEN_WIDHT / 2.f - 2.5f, 0);

    float lPlatformX = 20.f;
    float lPlatformY = SCREEN_HEIGHT / 2.f;
    sf::RectangleShape lPlatform(sf::Vector2f(PLATFORM_WIDHT, PLATFORM_HEIGHT));
    lPlatform.setFillColor(sf::Color::White);
    lPlatform.setOrigin(sf::Vector2f(PLATFORM_WIDHT / 2.f, PLATFORM_HEIGHT / 2.f));
    lPlatform.setPosition(lPlatformX, lPlatformY);

    float rPlatformX = SCREEN_WIDHT - 20.f;
    float rPlatformY = SCREEN_HEIGHT / 2.f;
    sf::RectangleShape rPlatform(sf::Vector2f(PLATFORM_WIDHT, PLATFORM_HEIGHT));
    rPlatform.setFillColor(sf::Color::White);
    rPlatform.setOrigin(sf::Vector2f(PLATFORM_WIDHT / 2.f, PLATFORM_HEIGHT / 2.f));
    rPlatform.setPosition(rPlatformX, rPlatformY);

    float ballX = SCREEN_WIDHT / 2.f;
    float ballY = SCREEN_HEIGHT / 2.f;
    sf::Vector2f directionBall = DirectionBallInStart();
    sf::CircleShape ball(RADIUS_BALL);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(sf::Vector2f(RADIUS_BALL, RADIUS_BALL));
    ball.setPosition(ballX, ballY);
    
    unsigned short scoreOfLPlatform = 0;
    unsigned short scoreOfRPlatform = 0;

    sf::Font font; 
    assert(font.loadFromFile(RESOURCES_PATH + "Font/Roboto-Medium.ttf"));
    sf::Text lScoreText;
    lScoreText.setString("0");
    lScoreText.setFont(font);
    lScoreText.setCharacterSize(48);
    lScoreText.setFillColor(sf::Color::White);
    lScoreText.setOrigin(GetTextOrigin(lScoreText, { 0.5f, 0.5f }));
    lScoreText.setPosition({ SCREEN_WIDHT / 4, SCREEN_HEIGHT / 5 });

    sf::Text rScoreText;
    rScoreText.setString("0");
    rScoreText.setFont(font);
    rScoreText.setCharacterSize(48);
    rScoreText.setFillColor(sf::Color::White);
    rScoreText.setOrigin(GetTextOrigin(rScoreText, { 0.5f, 0.5f }));
    rScoreText.setPosition({ SCREEN_WIDHT / 4 * 3, SCREEN_HEIGHT / 5 });

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (lPlatform.getPosition().y - PLATFORM_HEIGHT / 2) > 0)
        {
            lPlatform.setPosition({ lPlatform.getPosition().x, lPlatform.getPosition().y - INITIAL_SPEED_PLATFORM * deltaTime });
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (lPlatform.getPosition().y + PLATFORM_HEIGHT / 2) < SCREEN_HEIGHT)
        {
            lPlatform.setPosition({ lPlatform.getPosition().x, lPlatform.getPosition().y + INITIAL_SPEED_PLATFORM * deltaTime });
        }


        if (ball.getPosition().y < rPlatform.getPosition().y && (rPlatform.getPosition().y - PLATFORM_HEIGHT / 2) > 0)
        {
            rPlatform.setPosition({ rPlatform.getPosition().x, rPlatform.getPosition().y - INITIAL_SPEED_PLATFORM * deltaTime });
        }
        else if (ball.getPosition().y > rPlatform.getPosition().y && (rPlatform.getPosition().y + PLATFORM_HEIGHT / 2) < SCREEN_HEIGHT)
        {
            rPlatform.setPosition({ rPlatform.getPosition().x, rPlatform.getPosition().y + INITIAL_SPEED_PLATFORM * deltaTime });
        }

        if (ball.getPosition().x - RADIUS_BALL <= 0)
        {
            scoreOfLPlatform++;
        }
        else if (ball.getPosition().x >= SCREEN_WIDHT)
        {
            scoreOfRPlatform++;
        }

        if ((ball.getPosition().y - RADIUS_BALL) < 0 || (ball.getPosition().y + RADIUS_BALL) > SCREEN_HEIGHT)
        {
            directionBall.y *= -1;
        }

        if (FindPlatformCollisionWithBall(lPlatform, ball))
        {
            switch (GetPartOfPlatformWithCollision(lPlatform, ball))
            {
            case PartOfPlatform::Top:
                SetDirectionInCaseOfCollisionWithPlatform(directionBall, PartOfPlatform::Top);
                break;
            case PartOfPlatform::Down:
                SetDirectionInCaseOfCollisionWithPlatform(directionBall, PartOfPlatform::Down);
                break;
            case PartOfPlatform::Middle:
            default:
                directionBall.x *= -1;
                break;
            }
        }

        if (FindPlatformCollisionWithBall(rPlatform, ball))
        {
            switch (GetPartOfPlatformWithCollision(rPlatform, ball))
            {
            case PartOfPlatform::Top:
                SetDirectionInCaseOfCollisionWithPlatform(directionBall, PartOfPlatform::Top);
                break;
            case PartOfPlatform::Down:
                SetDirectionInCaseOfCollisionWithPlatform(directionBall, PartOfPlatform::Down);
                break;
            case PartOfPlatform::Middle:
            default:
                directionBall.x *= -1;
                break;
            }
        }
        ball.setPosition(ball.getPosition() + directionBall * deltaTime * INITIAL_SPEED_BALL);

        if (ball.getPosition().x - RADIUS_BALL <= lPlatform.getPosition().x)
        {
            scoreOfRPlatform++;
            lPlatform.setPosition(lPlatformX, lPlatformY);
            rPlatform.setPosition(rPlatformX, rPlatformY);
            directionBall = DirectionBallInStart();
            ball.setPosition(ballX, ballY);
        }
        else if (ball.getPosition().x + RADIUS_BALL >= rPlatform.getPosition().x)
        {
            scoreOfLPlatform++;
            lPlatform.setPosition(lPlatformX, lPlatformY);
            rPlatform.setPosition(rPlatformX, rPlatformY);
            directionBall = DirectionBallInStart();
            ball.setPosition(ballX, ballY);
        }

        lScoreText.setString(std::to_string(scoreOfLPlatform));
        rScoreText.setString(std::to_string(scoreOfRPlatform));

        window.clear();
        window.draw(separatorLine);
        window.draw(lPlatform);
        window.draw(rPlatform);
        window.draw(ball);
        window.draw(lScoreText);
        window.draw(rScoreText);
        window.display();
    }

    return 0;
}