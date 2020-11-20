#include "Player.h"
#include <iostream>

Player::Player(Ip remote, sf::UdpSocket *socket, sf::FloatRect shape, int layer, sf::Texture fond, int num, float speed, float poids, float vie) : Collision(shape, layer, fond),
					Sync(remote, socket), m_num(num), m_speed(speed), m_poids(poids), m_vie(vie), m_enVie(true), m_vieBar((int)vie, (int)vie, sf::Color::Red, sf::FloatRect(0, -20, m_shape.width, 20))
{

	m_gravity = 5.f;

	m_spl = SpellList();

	m_baseJump = 2000.f;
	m_jumpHeight = m_baseJump;
	m_jumping = false;


	

	m_nomJoueur.setFont(Utils::baseFont);

	m_nomJoueur.setFillColor(sf::Color::Black);

	m_nomJoueur.setString("Player " + std::to_string(num + 1));

	m_nomJoueur.setCharacterSize(20);

	m_nomJoueur.setPosition(sf::Vector2f(m_shape.left, m_shape.top - m_nomJoueur.getGlobalBounds().height - m_vieBar.getSize().y));

	CollisionList::getInstance()->addObject(this);
}


Player::~Player()
{
}

void Player::prepare(sf::Packet p)
{

	sf::Vector2f playerPos;
	sf::Vector2f mousePos;
	int spType;
	float px, py, mx, my;
	p >> m_dir >> m_jump;
	if (p >> spType >> px >> py >> mx >> my)
	{	
		playerPos = sf::Vector2f(px, py);
		mousePos = sf::Vector2f(mx, my);

		m_spl.castSpell(static_cast<Spell::Type>(spType), m_remote, m_socket, playerPos, mousePos);
	}

}

void Player::update(sf::Time delta)
{

	std::vector<Collision*> otherObject = CollisionList::getInstance()->getObjects();
	otherObject.erase(std::find(otherObject.begin(), otherObject.end(), this));

	std::vector<Spell *> m_listSpell = m_spl.getObjects();
	for (auto& sp : m_listSpell)
	{
		otherObject.erase(std::find(otherObject.begin(), otherObject.end(), sp));
	}


	//DEPLACEMENT---------------------------------------------------------------
	sf::Vector2f dir;

	//Choix de la direction 
	switch (m_dir)
	{
	case 1:
		dir.x -= m_speed;
		break;
	case 2:
		dir.x += m_speed;
		break;
	default:
		break;
	}

	dir.x *= delta.asSeconds();


	moveP(dir);
	//On teste les collisions
	if (collide(otherObject))
		moveP(-dir); //On annule le mouvement

	sf::Vector2f movement;

	//Application de la gravité
	movement.y += (m_gravity * m_poids);

	//On uniformise le mouvement selon le temps passé
	movement.y *= delta.asSeconds();

	moveP(movement);
	//On teste les collisions
	if (collide(otherObject))
	{
		m_jumpHeight = m_baseJump;
		moveP(-movement); //On annule le mouvement
	}
		

	//Application du saut
	sf::Vector2f saut;
	
	if (m_jump || m_jumping)
	{
		
		if (m_jumpHeight <= 0)
			m_jumping = false;		
		else
		{
			saut.y -= m_jumpHeight;
			m_jumpHeight -= 200;
			m_jumping = true;
		}
			
	}

	saut.y *= delta.asSeconds();
	moveP(saut);
	//On teste les collisions
	if (collide(otherObject))
		moveP(-saut); //On annule le mouvement


	m_dir = 0;
	m_jump = false;
	//FIN DEPLACEMENT---------------------------------------------------------------


	//SORT---------------------------------------------------------------
	int i = 0;
	std::vector<int> listToDelete = std::vector<int>();
	for (auto& sp : m_listSpell)
	{
		//On update tous les spells
		Collision *c = sp->update(delta);
		if (c != nullptr) //Si le spell à touché qqc, on l'enleve
		{
			if (c == this) //Si il nous touche nous meme on annule
				break;

			if (c->getType() == Collision::Object::PLAYER)
				damage((Player*)c, sp);

			CollisionList::getInstance()->removeObject(sp);
			m_spl.removeObject(sp);
		}

		if (!Utils::windowSize.contains((sf::Vector2i)sp->getPosition()))
		{
			CollisionList::getInstance()->removeObject(sp);
			m_spl.removeObject(sp);
		}
			

		i++;
	}

	//On enlève les sorts qui doivent être enlevées
	for (int i = listToDelete.size() - 1; i >= 0; i--)
	{
		m_listSpell.erase(m_listSpell.begin() + listToDelete[i]);
	}
	

	

 
}

void Player::moveP(sf::Vector2f mouv)
{
	Collision::moveP(mouv);
	m_nomJoueur.move(mouv);
}

Collision::Object Player::getType()
{
	return Object::PLAYER;
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_enVie)
	{
		Collision::draw(target, states);
		target.draw(m_nomJoueur);
		target.draw(m_vieBar);
		for (auto& sp : m_spl.getObjects())
		{
			target.draw(*sp);
		}
	}
}

SpellList * Player::getSpl()
{
	return &m_spl;
}

bool Player::isEnVie()
{
	return m_enVie;
}

void Player::damage(Player * p, Spell * sp)
{
	p->receiveDamage(sp);
}

void Player::receiveDamage(Spell * sp)
{
	m_vie -= sp->getDamage();
	m_vieBar.setValue((int)m_vie);
	if (m_vie <= 0)
	{
		m_enVie = false;
		//on change de layer pour éviter les collisions
		m_layer = -999;
	}
		
}
