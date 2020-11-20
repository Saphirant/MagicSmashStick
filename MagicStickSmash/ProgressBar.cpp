#include "ProgressBar.h"
#include "utils.h"



ProgressBar::ProgressBar(int max, int value, sf::Color barColor, sf::FloatRect pos): m_max(max), m_value(value), m_barColor(barColor)
{


	m_box.setPosition(sf::Vector2f(pos.left, pos.top));
	m_box.setSize(sf::Vector2f(pos.width, pos.height));
	m_box.setFillColor(sf::Color(40, 40, 40, 255));

	m_barre.setPosition(sf::Vector2f(pos.left, pos.top));
	m_barre.setSize(sf::Vector2f((m_value/m_max)* m_box.getSize().x, pos.height));
	m_barre.setFillColor(m_barColor);

	m_text.setFont(Utils::baseFont);

	m_text.setFillColor(sf::Color::Black);

	m_text.setString(std::to_string(m_value) + "/" + std::to_string(m_max));

	m_text.setCharacterSize(pos.height / 2);

	m_text.setPosition(sf::Vector2f(pos.left + pos.width / 2 - m_text.getGlobalBounds().width / 2, pos.top + pos.height / 2 - m_text.getGlobalBounds().height / 2));
}

ProgressBar::~ProgressBar()
{
}

sf::Vector2f ProgressBar::getSize()
{
	return m_box.getSize();
}


void ProgressBar::setValue(int value)
{
	if (value >= 0 && value <= m_max)
	{
		m_value = value;
		m_text.setString(std::to_string(m_value) + "/" + std::to_string(m_max));
		m_barre.setSize(sf::Vector2f((m_value / m_max)* m_box.getSize().x, m_barre.getSize().y));
	}
}

void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// on applique la transformation de l'entité -- on la combine avec celle qui a été passée par l'appelant
	states.transform *= getTransform(); // getTransform() est définie par sf::Transformable


	// on dessine le tableau de vertex
	target.draw(m_box, states);
	target.draw(m_barre, states);
	target.draw(m_text, states);
}
