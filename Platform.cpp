#include "Platform.h"

namespace PongGame
{
	void InitPlatform(Platform& platform, const int& side)
	{
		if (side == 0)
		{
			platform.position.x = 20.f;
		}
		else
		{
			platform.position.x = SCREEN_WIDHT - 20.f;
		}
		platform.position.y = SCREEN_HEIGHT / 2.f;
		platform.platformShape.setSize({ PLATFORM_WIDHT, PLATFORM_HEIGHT });
		platform.platformShape.setFillColor(sf::Color::White);
		platform.platformShape.setOrigin(sf::Vector2f(PLATFORM_WIDHT / 2.f, PLATFORM_HEIGHT / 2.f));
	}

	void UpdatePlatform(Platform& platform, float deltaTime)
	{

	}

	void DrawPlatform(Platform& platform, sf::RenderWindow& window)
	{
		platform.platformShape.setPosition(platform.position.x, platform.position.y);
		window.draw(platform.platformShape);
	}
}
