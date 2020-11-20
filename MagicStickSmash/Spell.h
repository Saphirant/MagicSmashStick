#pragma once
#include "CollisionList.h"
#include "Sync.h"
#include "utils.h"


class Spell :
	public Collision, public Sync
{
public:
	enum Type : int
	{
		SPELL_0 = 0,
		SPELL_1,
		SPELL_2,
		SPELL_3
	};

	Spell(Ip remote, sf::UdpSocket *socket, sf::FloatRect shape, int layer, sf::Texture fond, Spell::Type spType, sf::Vector2f origin, sf::Vector2f dest, sf::Time cd, float speed, float damage);
	~Spell();

	virtual Object getType();

	Collision * update(sf::Time delta);

	bool isOnCd();

	Spell::Type getSpellType();


	float getDamage();

private:
	Spell::Type m_spType;

	sf::Vector2f m_origin;
	sf::Vector2f m_dest;

	float m_speed;
	float m_damage;

	sf::Time m_cd;
	bool m_onCd;
	
};

