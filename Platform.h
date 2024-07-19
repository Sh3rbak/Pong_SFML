#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "GameSettings.h"

namespace PongGame
{
	struct Platform
	{
		Vector2D position;
		float speed = 0.f;
		sf::RectangleShape platformShape;
	};

	void InitPlatform(Platform& platform, const int& side);
	void UpdatePlatform(Platform& platform, float deltaTime);

	void DrawPlatform(Platform& platform, sf::RenderWindow& window);
}

