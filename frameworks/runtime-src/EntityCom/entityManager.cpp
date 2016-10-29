#include "entityManager.h"

namespace xyGame {

	unsigned int Entity::EID(1);

	Entity::Entity()
	:m_body(nullptr),
	m_id(0)
	{
	}

	Entity::~Entity()
	{
		CC_SAFE_RELEASE(m_body);
	}

	bool Entity::init(void)
	{
		m_body = Sprite::create();
		m_body->retain();
		m_id = EID;
		EID++;
		return false;
	}

	Entity * Entity::create(void)
	{
		Entity *pent = new (std::nothrow) Entity();
		pent->init();
		pent->autorelease();
		return pent;
	}

}