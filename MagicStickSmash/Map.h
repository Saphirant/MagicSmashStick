#pragma once
#include "Plateforme.h"
#include "CollisionList.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Texture.h"

class Map : public sf::Drawable, public sf::Transformable
{
private:
	//Liste de toutes les plateformes
	std::vector<Plateforme *> m_listPlateformes;

	//Liste des positions de départs de tous les joueurs
	std::vector<sf::Vector2f> m_listStartPos;

	//Nombre de joueur max
	int m_nbMax;

public:
	Map(std::string path);
	~Map();

	std::vector<sf::Vector2f> getListStartPos();

	int getNbMax();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

