#pragma once
#include "utils.h"
#include <SFML/Network.hpp>

class Sync
{
protected:

	/// <summary>
	/// Structure contenant l'adresse du serveur au quel est lié l'objet
	/// </summary>
	Ip m_remote;

	/// <summary>
	/// Socket d'envoi des informations
	/// </summary>
	sf::UdpSocket *m_socket;

	/// <summary>
	/// Packet contenant les dernieres informations recues
	/// </summary>
	sf::Packet m_receive;

	/// <summary>
	/// Packet contenant les infos à envoyé
	/// </summary>
	sf::Packet m_send;

	/// <summary>
	/// Envoi au serveur le packet m_send
	/// </summary>
	void send();



public:
	Sync(Ip remote, sf::UdpSocket *socket);
	~Sync();

	/// <summary>
	/// Recois des informations du serveur (et les place dans m_receive)
	/// </summary>
	/// <returns>infos recues</returns>
	sf::Packet receive();

	/// <summary>
	/// Envoie les infos passés en paramètres (plus celle de base)
	/// </summary>
	/// <param name="info">Info à passer</param>
	void send(sf::Packet info);
};

