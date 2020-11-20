#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"

class Plateforme : public Collision
{


public:
	Plateforme(sf::FloatRect shape, int layer, sf::Texture fond);
	~Plateforme();
	virtual Object getType();
};

