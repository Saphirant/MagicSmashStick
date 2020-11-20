#include "CollisionList.h"

CollisionList * CollisionList::instance = new CollisionList();

CollisionList::CollisionList()
{
	listCollision = std::vector<Collision *>();
}


CollisionList::~CollisionList()
{
	for (auto& c : listCollision)
	{
		delete c;
	}
}

Collision * CollisionList::addObject(Collision * o)
{
	listCollision.push_back(o);
	return o;
}

void CollisionList::removeObject(Collision * o)
{
	auto pos = std::find(listCollision.begin(), listCollision.end(), o);
	if (pos != listCollision.end())
		listCollision.erase(pos);
	
}

std::vector<Collision*> CollisionList::getObjects()
{
	return std::vector<Collision*>(listCollision);
}

CollisionList * CollisionList::getInstance()
{
	return instance;
}
