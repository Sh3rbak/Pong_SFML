#include "Math.h"

namespace PongGame
{
    Vector2D NormalizeVector(const Vector2D& vector)
    {
        const float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);
        Vector2D normalizeVector;
        normalizeVector.x = vector.x / magnitude;
        normalizeVector.y = vector.y / magnitude;
        return normalizeVector;
    }

    sf::Vector2f GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition)
    {
        sf::FloatRect textSize = text.getLocalBounds();
        return {
            (textSize.left + textSize.width) * relativePosition.x,
            (textSize.top + textSize.height) * relativePosition.y,
        };
    }
}