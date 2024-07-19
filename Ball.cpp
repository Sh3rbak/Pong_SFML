#include "Ball.h"

namespace PongGame
{
	void InitBall(Ball& ball)
	{
        ball.position.x = SCREEN_WIDHT / 2.f;
        ball.position.y = SCREEN_HEIGHT / 2.f;
        ball.direction = DirectionBallInStart();
        ball.ballShape.setRadius(RADIUS_BALL);
        ball.ballShape.setFillColor(sf::Color::White);
        ball.ballShape.setOrigin(sf::Vector2f(RADIUS_BALL, RADIUS_BALL));
        
	}

	void UpdateBall(Ball& ball, const float deltaTime)
	{

	}

    Vector2D DirectionBallInStart()
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

    bool FindPlatformCollisionWithBall(const Vector2D& platformPosition, const Ball& ball)
    {
        const float deltaX = abs(platformPosition.x - ball.position.x);
        const float deltaY = abs(platformPosition.y - ball.position.y);

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

    void ChangeDirectionInCaseOfBallCollisionWithPlatform(Ball& ball, Vector2D& platformPosition)
    {
        float sqrDirectionX = ball.direction.x * ball.direction.x;
        float sqrDirectionY = ball.direction.y * ball.direction.y;
        const float sqrDirection = sqrDirectionX + sqrDirectionY;

        if (ball.position.y < platformPosition.y - PLATFORM_HEIGHT / 6)
        {
            ball.direction.y -= 0.3f;
        }
        if (ball.position.y > platformPosition.y + PLATFORM_HEIGHT / 6)
        {
            ball.direction.y += .3f;
        }

        if (ball.direction.y >= 0.9f)
        {
            ball.direction.y = 0.9f;
        }
        else if (ball.direction.y <= -0.9f)
        {
            ball.direction.y = -0.9f;
        }

        sqrDirectionY = ball.direction.y * ball.direction.y;
        sqrDirectionX = abs(sqrDirection - sqrDirectionY);
        if (ball.direction.x > 0)
        {
            ball.direction.x = sqrt(sqrDirectionX) * -1.f;
        }
        else
        {
            ball.direction.x = sqrt(sqrDirectionX);
        }
    }
	void DrawBall(Ball& ball, sf::RenderWindow& window)
	{
        ball.ballShape.setPosition(ball.position.x, ball.position.y);
        window.draw(ball.ballShape);
	}
}
