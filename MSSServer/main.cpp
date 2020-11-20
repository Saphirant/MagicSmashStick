#include <iostream>
#include <vector>
#include <string>
#include <SFML/Network.hpp>

typedef struct Ip {
	sf::IpAddress recipient;
	unsigned short port;
}Ip;



bool contains(const std::vector<Ip> &listConnecte, const Ip &client)
{
	for (auto& c : listConnecte)
	{
		if (c.recipient == client.recipient && c.port == client.port)
			return true;
	}
	return false;
}


int main()
{

	//Nombre de personne connecté
	int nJoueurs = 2;
	std::cout << "Nombre de joueurs: ";
	std::cin >> nJoueurs;


	while (true)
	{
		unsigned short port = 25565;

		std::cout << "Server port: " << port << std::endl;

		//Socket d'écoute du serveur
		sf::UdpSocket listener;

		
		//Liste des personnes connectés
		std::vector<Ip> listConnecte = std::vector<Ip>();

		//On lie le socket au port
		if (listener.bind(port) != sf::Socket::Done)
		{
			std::cout << "Erreur lors de l'attribution du port : " << port << std::endl;
			return 1;
		}

		//On accepte le bon nombre de connection
		for (int i = 0; i < nJoueurs; i++)
		{
			Ip client;
			sf::Packet p;

			if (listener.receive(p, client.recipient, client.port) != sf::Socket::Done)
			{
				std::cout << "Erreur lors de la connexion du " << i + 1 << "eme joueur" << std::endl;
				return 1;
			}

			if (!contains(listConnecte, client))
			{
				listConnecte.push_back(client);
				std::cout << "Connexion du " << i + 1 << "eme joueur" << std::endl;

			}
			else
			{
				std::cout << "Utilisateur " << client.recipient << ":" << client.port << " deja connecte" << std::endl;
				i--;
			}

		}
		std::cout << "Debut des communications" << std::endl;
		//Envoie des informations aux joueurs (leur numéro et le nombre de joueur total)
		for (int i = 0; i < nJoueurs; i++)
		{
			Ip client = listConnecte[i];
			sf::Packet p;
			p << i << nJoueurs;
			listener.send(p, client.recipient, client.port);
		}

		//Boucle principale	
		bool stop = false;
		while (!stop)
		{
			Ip sender;
			sf::Packet packet;

			if (listener.receive(packet, sender.recipient, sender.port) == sf::Socket::Done)
			{
				std::string r;
				if (packet >> r)
					if (r == "fin")
						break;

				//std::cout << "Packet recues" << std::endl;

				//on recoit les informations et on les renvoie à tous le monde
				for (auto &s : listConnecte)
				{

					//if (!s.recipient.toString().compare(sender.recipient.toString()) && s.port != sender.port)//on ne lui renvoie pas les infos				
						listener.send(packet, s.recipient, s.port);
					
						
				}
			}
			else
				std::cout << "Erreur lors de la reception de certaines donnees" << std::endl;

		}

		//On attends la deconnexion de tous les joueurs avant de quitter
		int i = nJoueurs - 1;
		while(i > 0)
		{
			Ip sender;
			sf::Packet packet;

			listener.receive(packet, sender.recipient, sender.port);
			std::string r;
			if (packet >> r)
				if (r == "fin")
					i--;
		}

		std::cout << "Fin des communications" << std::endl;

		listener.unbind();
	}

	return 0;
}

