#include <iostream>
#include <SFML/Network.hpp>
#include <thread>
#include "Player.h"
#include "Map.h"

bool stopThread = false;
bool updatePlayer = false;

sf::Packet threadP;

void receive(sf::UdpSocket * socket, sf::SocketSelector * selector, std::vector<Player*> listPlayer)
{

	while (!stopThread)
	{
		Ip remote;
		sf::Packet p;
		if (selector->wait(sf::seconds(1)))
		{
			socket->receive(threadP, remote.recipient, remote.port);
			updatePlayer = true;
			
			
		}
	}

}


int main()
{


	//Mise en place basique du réseau 
	Ip remote;
	remote.recipient = "127.0.0.1";
	remote.port = 25565;

	unsigned short port;

	sf::UdpSocket socket;
	//On connecte le socket
	if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
	{
		std::cout << "Erreur lors de la connection"<< std::endl;
		return 1;
	}
	port = socket.getLocalPort();
	
	//On dit au serveur qu'on existe
	sf::Packet s;
	if (socket.send(s, remote.recipient, remote.port) != sf::Socket::Done)
	{
		std::cout << "Erreur lors de la connection à " << remote.recipient << ":" << remote.port << std::endl;
		return 1;
	}
	//Reception des infos du serveur
	sf::Packet info;
	if (socket.receive(info, remote.recipient, remote.port) != sf::Socket::Done)
	{
		std::cout << "Erreur lors de la connection à " << remote.recipient << ":" << remote.port << std::endl;
		return 1;
	}
	
	int nJoueurs;
	int numPlayer;
	info >> numPlayer >> nJoueurs;

	sf::SocketSelector selector;
	selector.add(socket);


	sf::RenderWindow window(sf::VideoMode(1280, 720), "MagicStickSmash - Player " + std::to_string(numPlayer + 1));

	Utils::windowSize = sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)window.getSize());

	//Mise en place du jeu
	Utils::baseFont.loadFromFile("Ressources\\Font\\basic.otf");

	

	//Chargement des textures
	Texture *texture = Texture::getInstance();

	//Chargement de la map
	Map map = Map("Ressources\\Map\\map_0.txt");

	if (map.getNbMax() < nJoueurs)
	{
		std::cout << "Erreur lors de la création de la partie, il y a trop de joueurs " << std::endl;
		return 1;
	}

	std::vector<sf::Vector2f> startPos = map.getListStartPos();

	//Initialisation de tous les joueurs
	std::vector<Player*> listPlayer = std::vector<Player*>();
	for (int i = 0; i < nJoueurs; i++)
	{
		Player *p = new Player(remote, &socket, sf::FloatRect(startPos[i], sf::Vector2f(80, 170)), 0, texture->player_0, i, 500, 80, 20.f);
		listPlayer.push_back(p);
	}


	//Démarage du thread de réception des messages
	std::thread tRecep(receive, &socket, &selector, listPlayer);

	//Horloge du jeu
	sf::Clock clock;
	
		

	

	
	//cl.addObject(new Plateforme(sf::FloatRect(0, 300, 400, 100), 0, texture.plateforme_0));


	window.setFramerateLimit(60);


	while (window.isOpen())
	{
		sf::Packet choix;
		bool changement = false;

		choix << numPlayer;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && window.hasFocus())
		{
			changement = true;
			choix << 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && window.hasFocus())
		{
			changement = true;
			choix << 2;
		}
		else
			choix << 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && window.hasFocus())
		{
			choix << true;
			changement = true;
		}
		else
			choix << false;




		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				sf::Packet p;
				p << "fin";
				socket.send(p, remote.recipient, remote.port);
				window.close();
				stopThread = true;
			}
			else if (event.type == sf::Event::Resized)
			{
				// on met à jour la vue, avec la nouvelle taille de la fenêtre
				sf::FloatRect visibleArea(0.f, 0.f, (float)event.size.width, (float)event.size.height);
				window.setView(sf::View(visibleArea));
			}
			else if (event.type == sf::Event::KeyPressed )
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					sf::Packet p;
					p << "fin";
					socket.send(p, remote.recipient, remote.port);
					window.close();
					stopThread = true;
				}

				if (event.key.code == sf::Keyboard::LShift)
				{
					if (!listPlayer[numPlayer]->getSpl()->isSpellOnCd(Spell::Type::SPELL_0))
					{
						sf::Vector2f localPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
						choix << Spell::Type::SPELL_0 << listPlayer[numPlayer]->getPosition().x << listPlayer[numPlayer]->getPosition().y << localPosition.x << localPosition.y;
						changement = true;
					}
						
				}
				
			}
			


				
		}



		if (changement)
			socket.send(choix, remote.recipient, remote.port);



		if (updatePlayer)
		{
			//Récupération du numéro du joueur
			int numP;
			threadP >> numP;
			//std::cout << "Info recues de " << numP +1 << std::endl;
			listPlayer[numP]->prepare(threadP);

			updatePlayer = false;
		}

		sf::Time elapsed = clock.restart();

		//Mise à jour de la physique de tous les joueurs
		for (auto& player : listPlayer)
		{
			player->update(elapsed);
		}

		

		window.clear(sf::Color::White);


		//On dessine les joueurs (qui dessineront leurs sorts)
		for (auto& p : listPlayer)
		{
			window.draw(*p);
		}

		//On dessine la map
		window.draw(map);

		window.display();
	}
	
	tRecep.join();

	return 0;
}
