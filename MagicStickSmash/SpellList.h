#pragma once
#include <vector>
#include "Spell.h"

class SpellList
{
private:
	std::vector<Spell *> m_listSpell;
public:
	SpellList();
	~SpellList();

	Spell* castSpell(Spell::Type spType, Ip remote, sf::UdpSocket * socket, sf::Vector2f playerPos, sf::Vector2f mousePos);
	void removeObject(Spell* o);
	std::vector<Spell *> getObjects() const;

	bool isSpellOnCd(Spell::Type spType);



};

