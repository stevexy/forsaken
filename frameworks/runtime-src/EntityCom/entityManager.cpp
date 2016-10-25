#include "entityManager.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

bool Entity::init(void)
{
	return false;
}

Entity * Entity::create(void)
{
	Entity *pent = new (std::nothrow) Entity();
	pent->init();
	pent->autorelease();

	return pent;
}
