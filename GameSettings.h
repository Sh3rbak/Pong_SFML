#pragma once
#include <string>

namespace PongGame
{
	const std::string RESOURCES_PATH = "Assets/";

	const int SCREEN_HEIGHT = 720;
	const int SCREEN_WIDHT = 1240;
	const float PLATFORM_HEIGHT = SCREEN_HEIGHT / 8.f;
	const float PLATFORM_WIDHT = SCREEN_WIDHT / 100.f;
	const float RADIUS_BALL = SCREEN_WIDHT / 120.f;

	const float INITIAL_SPEED_PLATFORM = 250.f;
	const float INITIAL_SPEED_BALL = 300.f;
}