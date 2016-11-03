#include "entityManager.h"

namespace xyGame {

	unsigned int Entity::EID(1);

	Entity::Entity()
	:root_node(nullptr),
	m_body(nullptr),
	m_id(0),
	_speed(60)
	{
	}

	Entity::~Entity()
	{
		CC_SAFE_RELEASE(m_body);
		CC_SAFE_RELEASE(root_node);
	}

	bool Entity::init(void)
	{
		root_node = Node::create();
		root_node->retain();
		m_body = Sprite::create();
		root_node->addChild(m_body,3);
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

	void Entity::set_direction(int dir)
	{
		switch (dir)
		{
			case 1:
				_direction = left;
				break;
			case 2:
				_direction = right;
				break;
			case 3:
				_direction = up;
				break;
			case 4:
				_direction = down;
				break;
			default:
				_direction = idle;
		}
	}
	void Entity::update(float deltatime)
	{
		Vec2 position = root_node->getPosition();
		switch (_direction)
		{
		case xyGame::idle:
			break;
		case xyGame::left:
			position.x -= _speed*deltatime;
			break;
		case xyGame::right:
			position.x += _speed*deltatime;
			break;
		case xyGame::up:
			position.y += _speed*deltatime;
			break;
		case xyGame::down:
			position.y -= _speed*deltatime;
			break;
		default:
			break;
		}
		root_node->setPosition(position);
	}
}