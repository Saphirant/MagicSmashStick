#include "Collision.h"




Collision::Collision(sf::FloatRect shape, int layer, sf::Texture fond): m_shape(shape), m_layer(layer), m_fond(fond)
{
	m_box = sf::RectangleShape(sf::Vector2f(shape.width, shape.height));
	move(sf::Vector2f(shape.left, shape.top));

	m_box.setTexture(&m_fond);
}

Collision::~Collision()
{
}

bool Collision::collide(std::vector<Collision*> otherObject)
{
	for (auto& obj : otherObject)
	{
		if (obj->m_layer == m_layer)
			if (obj->m_shape.intersects(m_shape))
				return true;
	}
	return false;
}

std::vector<Collision*> Collision::getColliding(std::vector<Collision*> otherObject)
{
	std::vector<Collision*> res = std::vector<Collision*>();
	for (auto& obj : otherObject)
	{
		if (obj->m_layer == m_layer)
			if (obj->m_shape.intersects(m_shape))
				res.push_back(obj);
	}
	return res;
}

void Collision::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// on applique la transformation de l'entité -- on la combine avec celle qui a été passée par l'appelant
	states.transform *= getTransform(); // getTransform() est définie par sf::Transformable



	// on dessine le tableau de vertex
	target.draw(m_box, states);
}


void Collision::moveP(sf::Vector2f mouv)
{
	move(mouv);
	m_shape.top += mouv.y;
	m_shape.left += mouv.x;
}

