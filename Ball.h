#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "GameSettings.h"

namespace PongGame
{
	enum class DirectionBall : std::uint8_t
	{
		Right,
		Left
	};

	struct Ball
	{
		Position position;
		float speed;
		Vector2D direction;
		sf::CircleShape ballShape;
	};
	
	void InitBall(Ball& ball);
	void UpdateBall(Ball& ball, const float deltaTime);
	Vector2D DirectionBallInStart();
	bool FindPlatformCollisionWithBall(const Vector2D& platformPosition, const Ball& ball);
	void ChangeDirectionInCaseOfBallCollisionWithPlatform(Ball& ball, Vector2D& platformPosition);
	void DrawBall(Ball& ball, sf::RenderWindow& window);
}
