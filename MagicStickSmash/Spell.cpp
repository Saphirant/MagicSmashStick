#include "Spell.h"


Spell::Spell(Ip remote, sf::UdpSocket *socket, sf::FloatRect shape, int layer, sf::Texture fond, Spell::Type spType, sf::Vector2f origin, sf::Vector2f dest, sf::Time cd, float speed, float damage): 
			Collision(shape, layer, fond), Sync(remote, socket), m_origin(origin) , m_dest(dest), m_speed(speed) , m_damage(damage), m_spType(spType), m_cd(cd), m_onCd(true)
{
	CollisionList::getInstance()->addObject(this);
}


Spell::~Spell()
{
}

Collision::Object Spell::getType()
{
	return Object::SPELL;
}

Collision * Spell::update(sf::Time delta)
{
	sf::Vector2f mouv = Utils::normalize(m_dest - m_origin);

	mouv.x *= m_speed * delta.asSeconds();
	mouv.y *= m_speed * delta.asSeconds();

	std::vector<Collision*> otherObject = CollisionList::getInstance()->getObjects();
	otherObject.erase(std::find(otherObject.begin(), otherObject.end(), this));

	moveP(mouv);

	if (collide(otherObject))
		return getColliding(otherObject)[0];
	
	if (!m_onCd && m_cd - delta <= sf::Time::Zero)
		m_onCd = false;
	else if (!m_onCd)
		m_cd -= delta;

	


	return nullptr;
}



bool Spell::isOnCd()
{
	return m_onCd;
}

Spell::Type Spell::getSpellType()
{
	return m_spType;
}

float Spell::getDamage()
{
	return m_damage;
}

