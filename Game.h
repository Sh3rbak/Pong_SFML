#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "GameSettings.h"
#include "Platform.h"
#include "Ball.h"

namespace PongGame
{
	enum class SideOfGameField
	{
		Right = 0,
		Left
	};

	struct Game
	{
		Platform rPlatform;
		Platform lPlatform;
		Ball ball;
		sf::RectangleShape separatorLine;

		unsigned short scoreOfLPlatform = 0;
		unsigned short scoreOfRPlatform = 0;

		sf::Font font;
		sf::Text lScoreText;
		sf::Text rScoreText;
	};

	void InitGame(Game& game);
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	void UpdateGame(Game& game, const float& deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
}
