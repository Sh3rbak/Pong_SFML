#include <cassert>
#include "Game.h"
namespace PongGame
{
    void InitGame(Game& game)
    {
        InitBall(game.ball);
        InitPlatform(game.lPlatform, 0);
        InitPlatform(game.rPlatform, 1);

        game.separatorLine.setScale(sf::Vector2f(5.f, SCREEN_HEIGHT));
        game.separatorLine.setPosition(SCREEN_WIDHT / 2.f - 2.5f, 0);

        assert(game.font.loadFromFile(RESOURCES_PATH + "Font/Roboto-Medium.ttf"));
        game.lScoreText.setString("0");
        game.lScoreText.setFont(game.font);
        game.lScoreText.setCharacterSize(48);
        game.lScoreText.setFillColor(sf::Color::White);
        game.lScoreText.setOrigin(GetTextOrigin(game.lScoreText, { 0.5f, 0.5f }));
        game.lScoreText.setPosition({ SCREEN_WIDHT / 4, SCREEN_HEIGHT / 5 });

        game.rScoreText.setString("0");
        game.rScoreText.setFont(game.font);
        game.rScoreText.setCharacterSize(48);
        game.rScoreText.setFillColor(sf::Color::White);
        game.rScoreText.setOrigin(GetTextOrigin(game.rScoreText, { 0.5f, 0.5f }));
        game.rScoreText.setPosition({ SCREEN_WIDHT / 4 * 3, SCREEN_HEIGHT / 5 });
    }

    void HandleWindowEvents(Game& game, sf::RenderWindow& window)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    void UpdateGame(Game& game, const float& deltaTime)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (game.lPlatform.position.y - PLATFORM_HEIGHT / 2) > 0)
        {
            game.lPlatform.position.y -= INITIAL_SPEED_PLATFORM * deltaTime;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (game.lPlatform.position.y + PLATFORM_HEIGHT / 2) < SCREEN_HEIGHT)
        {
            game.lPlatform.position.y += INITIAL_SPEED_PLATFORM * deltaTime;
        }

        if (game.ball.position.y < game.rPlatform.position.y && 
            (game.rPlatform.position.y - PLATFORM_HEIGHT / 2) > 0)
        {
            game.rPlatform.position.y -= INITIAL_SPEED_PLATFORM * deltaTime;
        }
        else if (game.ball.position.y > game.rPlatform.position.y && 
            (game.rPlatform.position.y + PLATFORM_HEIGHT / 2) < SCREEN_HEIGHT)
        {
            game.rPlatform.position.y += INITIAL_SPEED_PLATFORM * deltaTime;
        }

        if ((game.ball.position.y - RADIUS_BALL) < 0 || (game.ball.position.y + RADIUS_BALL) > SCREEN_HEIGHT)
        {
            game.ball.direction.y *= -1;
        }

        if (FindPlatformCollisionWithBall(game.lPlatform.position, game.ball))
        {
            ChangeDirectionInCaseOfBallCollisionWithPlatform(game.ball, game.lPlatform.position);
        }

        if (FindPlatformCollisionWithBall(game.rPlatform.position, game.ball))
        {
            ChangeDirectionInCaseOfBallCollisionWithPlatform(game.ball, game.rPlatform.position);
        }

        game.ball.position.x += game.ball.direction.x * deltaTime * INITIAL_SPEED_BALL;
        game.ball.position.y += game.ball.direction.y * deltaTime * INITIAL_SPEED_BALL;

        if (game.ball.position.x - RADIUS_BALL <= game.lPlatform.position.x)
        {
            game.scoreOfRPlatform++;
            InitPlatform(game.lPlatform, 0);
            InitPlatform(game.rPlatform, 1);
            game.ball.direction = DirectionBallInStart();
            game.ball.position.x = SCREEN_WIDHT / 2.f;
            game.ball.position.y = SCREEN_HEIGHT / 2.f;
        }
        else if (game.ball.position.x + RADIUS_BALL >= game.rPlatform.position.x)
        {
            game.scoreOfRPlatform++;
            InitPlatform(game.lPlatform, 0);
            InitPlatform(game.rPlatform, 1);
            game.ball.direction = DirectionBallInStart();
            game.ball.position.x = SCREEN_WIDHT / 2.f;
            game.ball.position.y = SCREEN_HEIGHT / 2.f;
        }

        game.lScoreText.setString(std::to_string(game.scoreOfLPlatform));
        game.rScoreText.setString(std::to_string(game.scoreOfRPlatform));
    }
    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        DrawBall(game.ball, window);
        DrawPlatform(game.lPlatform, window);
        DrawPlatform(game.rPlatform, window);
        window.draw(game.separatorLine);
        window.draw(game.lScoreText);
        window.draw(game.rScoreText);
    }
}