#include "Sync.h"




Sync::Sync(Ip remote, sf::UdpSocket *socket) : m_remote(remote), m_socket(socket)
{
}


Sync::~Sync()
{
}

sf::Packet Sync::receive()
{
	sf::Socket::Status status;
	if ((status = m_socket->receive(m_receive, m_remote.recipient, m_remote.port)) != sf::Socket::Done)
	{
		throw "Erreur lors de la recpetion du message. Code " + status;
	}
	return m_receive;
}

void Sync::send()
{
	sf::Socket::Status status;
	if ((status = m_socket->send(m_send, m_remote.recipient, m_remote.port)) != sf::Socket::Done)
	{
		throw "Erreur lors de l'envoi du message. Code " + status;
	}
}


void Sync::send(sf::Packet info)
{
	m_send << info;
	send();
}
