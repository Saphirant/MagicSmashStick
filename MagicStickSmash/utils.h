#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
typedef struct Ip {
	sf::IpAddress recipient;
	unsigned short port;
}Ip;

class Utils
{
public:
	~Utils() = delete;

	Utils() = delete;

	static sf::Vector2f normalize(const sf::Vector2f& source);

	static sf::IntRect windowSize;

	static sf::Font baseFont;
private:
};


