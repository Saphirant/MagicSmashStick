#include "Plateforme.h"



Plateforme::Plateforme(sf::FloatRect shape, int layer, sf::Texture fond): Collision(shape, layer, fond)
{
	
}

Plateforme::~Plateforme()
{
}

Collision::Object Plateforme::getType()
{
	return Object::PLATEFORME;
}

