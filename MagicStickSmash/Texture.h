#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Texture
{
private:
	static Texture * instance;
public:
	Texture();
	sf::Texture plateforme_0;
	sf::Texture player_0;
	sf::Texture explosion_0;


	sf::Texture getTextureByName(std::string name);


	static Texture* getInstance();

};
