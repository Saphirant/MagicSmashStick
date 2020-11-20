#include "utils.h"

sf::IntRect Utils::windowSize = sf::IntRect();

sf::Font Utils::baseFont = sf::Font();

sf::Vector2f Utils::normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}