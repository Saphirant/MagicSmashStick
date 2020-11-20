#include "SpellList.h"
#include "Texture.h"



SpellList::SpellList()
{
	m_listSpell = std::vector<Spell *>();
}


SpellList::~SpellList()
{
	for (auto& sp : m_listSpell)
	{
		delete sp;
	}
}

Spell * SpellList::castSpell(Spell::Type spType, Ip remote, sf::UdpSocket * socket, sf::Vector2f playerPos, sf::Vector2f mousePos)
{
	Spell * res;
	Texture * t = Texture::getInstance();

	sf::Vector2f size = sf::Vector2f(64, 64);
	sf::Time cd = sf::seconds(3);
	if (spType == Spell::Type::SPELL_0)
		res = new Spell(remote, socket, sf::FloatRect(playerPos, size), 0, t->explosion_0, spType, playerPos, sf::Vector2f(mousePos.x - size.x / 2, mousePos.y - size.y / 2),cd, 800, 5);


	m_listSpell.push_back(res);
	return res;
}

void SpellList::removeObject(Spell * o)
{
	auto pos = std::find(m_listSpell.begin(), m_listSpell.end(), o);
	if (pos != m_listSpell.end())
		m_listSpell.erase(pos);
}

std::vector<Spell*> SpellList::getObjects() const
{
	return std::vector<Spell*>(m_listSpell);
}

bool SpellList::isSpellOnCd(Spell::Type spType)
{
	for (auto& sp : m_listSpell)
	{
		if (sp->getSpellType() == spType)
			if (sp->isOnCd())
				return true;
	}
	return false;
}
