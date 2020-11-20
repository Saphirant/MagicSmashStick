#include "Texture.h"


Texture * Texture::instance = new Texture();

Texture::Texture()
{
	plateforme_0.loadFromFile("Ressources\\Images\\Plateforme\\plateforme_0.png");
	player_0.loadFromFile("Ressources\\Images\\Player\\player_0.png");
	explosion_0.loadFromFile("Ressources\\Images\\Spell\\explosion_0.png");
}

sf::Texture Texture::getTextureByName(std::string name)
{
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	if (name.compare("plateforme_0") == 0)
		return plateforme_0;
	if (name.compare("player_0") == 0)
		return player_0;
	if (name.compare("explosion_0") == 0)
		return explosion_0;
	return plateforme_0;
}

Texture * Texture::getInstance()
{
	return instance;
}
