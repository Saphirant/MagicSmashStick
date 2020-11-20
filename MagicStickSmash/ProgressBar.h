#pragma once
#include <SFML/Graphics.hpp>


class ProgressBar : public sf::Drawable, public sf::Transformable
{
private:
	sf::RectangleShape m_box;
	sf::RectangleShape m_barre;
	sf::Text m_text;

	sf::Color m_barColor;

	int m_max;
	int m_value;

public:
	ProgressBar(int max, int value, sf::Color barColor, sf::FloatRect pos);
	~ProgressBar();

	sf::Vector2f getSize();

	void setValue(int value);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

