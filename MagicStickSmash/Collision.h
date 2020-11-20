#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Collision : public sf::Drawable, public sf::Transformable
{
protected:
	sf::FloatRect m_shape;
	int m_layer;

	sf::Texture m_fond;
	sf::RectangleShape m_box;


public:
	enum Object
	{
		PLATEFORME = 0,
		PLAYER,
		SPELL
	};

	Collision(sf::FloatRect shape, int layer, sf::Texture fond);
	~Collision();	

	bool collide(std::vector<Collision*> otherObject);

	std::vector<Collision *> getColliding(std::vector<Collision*> otherObject);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void moveP(sf::Vector2f mouv);

	virtual Object getType() = 0;



};
