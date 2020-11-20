#pragma once
#include <vector>
#include "Collision.h"
class CollisionList
{
private:
	static CollisionList * instance;
	std::vector<Collision *> listCollision;
public:
	CollisionList();
	~CollisionList();

	Collision* addObject(Collision* o);
	void removeObject(Collision* o);
	std::vector<Collision *> getObjects();

	static CollisionList * getInstance();
};

