#pragma once
#include <SFML/Graphics.hpp>

namespace PongGame
{
	struct Vector2D
	{
		float x = 0.f;
		float y = 0.f;
	};
	typedef Vector2D Position;

	Vector2D NormalizeVector(const Vector2D& vector);
	sf::Vector2f GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition);
}

