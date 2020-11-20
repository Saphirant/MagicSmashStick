#include "Map.h"
#include <fstream>
#include <string>

Map::Map(std::string path) : m_nbMax(0)
{

	Texture * t = Texture::getInstance();

	std::string line;
	std::ifstream myfile(path);
	if (myfile.is_open())
	{
		getline(myfile, line);
		
		//On récupère la position de chaque joueur et le nombre de joueurs
		std::string s = line;
		std::string delimiter = ";";

		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);

			size_t temp = token.find('/');

			std::string pos1 = token.substr(0, temp);
			std::string pos2 = token.substr(temp, token.length());

			m_listStartPos.push_back(sf::Vector2f(std::strtof(pos1.c_str(),0), 
												  std::strtof(pos2.c_str(), 0)));


			s.erase(0, pos + delimiter.length());
			m_nbMax++;
		}
		m_nbMax++;
		m_listStartPos.push_back(sf::Vector2f(std::strtof(s.substr(0, s.find('/')).c_str(), 0), std::strtof(s.substr(s.find('/'), s.length()).c_str(), 0)));


		//On récupère toutes les plateformes
		while (getline(myfile, line))
		{
			std::string s = line;
			std::string delimiter = ";";

			float posRect[5];

			size_t pos = 0;
			std::string token;
			int i = 0;
			while ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);

				posRect[i] = std::strtof(token.c_str(), 0);

				s.erase(0, pos + delimiter.length());
				i++;
			}

			Plateforme * p = new Plateforme(sf::FloatRect(posRect[1], posRect[2], posRect[3], posRect[4]), (int)posRect[0], t->getTextureByName(s));
			m_listPlateformes.push_back(p);
			CollisionList::getInstance()->addObject(p);

		}

		myfile.close();
	}

	else 
		std::cout << "Unable to open " << path << std::endl;

}


Map::~Map()
{
}

std::vector<sf::Vector2f> Map::getListStartPos()
{
	return std::vector<sf::Vector2f>(m_listStartPos);
}

int Map::getNbMax()
{
	return m_nbMax;
}


void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// on applique la transformation de l'entité -- on la combine avec celle qui a été passée par l'appelant
	states.transform *= getTransform(); // getTransform() est définie par sf::Transformable


	for (auto& p : m_listPlateformes)
	{
		target.draw(*p);
	}
	// on dessine le tableau de vertex
}