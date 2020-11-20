#pragma once
#include "Sync.h"
#include "Collision.h"
#include "CollisionList.h"
#include <SFML/Graphics.hpp>
#include "SpellList.h"
#include "ProgressBar.h"


///Définition du contenu du packet d'information d'un joueur:
///int: Direction du déplacement du joueur:
///		- 0 : rien
///		- 1 : gauche
///		- 2 : droite
///bool: Est-ce que le personnage est en train de sauter (0: non, 1: oui)
///string: Nom du sort lancé
///float: position x du joueur
///float: position y du joueur
///float: position x de la souris
///float: position y de la souris
class Player :
	public Sync, public Collision
{
private:
	//Information envoyé par le réseau
	int m_num;
	bool m_jump;
	int m_dir;


	//Vitesse de déplacement (300 < 700)
	float m_speed;

	//Variable de gravité et de poids
	float m_gravity;
	float m_poids;

	//Variable de saut
	bool m_jumping;
	float m_jumpHeight;
	float m_baseJump;

	//Variable pour les sorts
	SpellList m_spl;

	//Variable de combat
	float m_vie;
	bool m_enVie;

	//Partie affichage
	sf::Text m_nomJoueur;
	ProgressBar m_vieBar;
public:
	Player(Ip remote, sf::UdpSocket *socket, sf::FloatRect shape, int layer, sf::Texture fond, int num, float speed, float poids, float vie);
	~Player();

	//Récupération des informations
	void prepare(sf::Packet p);

	//Mise à jour de la physique
	void update(sf::Time delta);

	void moveP(sf::Vector2f mouv);

	virtual Object getType();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	SpellList * getSpl();

	bool isEnVie();

	void damage(Player *p, Spell * sp);
	void receiveDamage(Spell * sp);

};

