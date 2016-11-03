#pragma once
#include "cocos2d.h"

using namespace cocos2d;

namespace xyGame {
	enum direction { idle,left, right, up, down };

	class Entity : public Ref
	{
	public:
		static unsigned int EID;
		Entity();
		~Entity();

		int _speed;
		direction _direction;
		unsigned int get_eid() { return m_id; }
		Sprite* get_sprite() { return m_body; };
		Node* get_root() { return root_node; };
		bool init(void);
		static Entity* create(void);
		void set_direction(int dir);
		void update(float deltatime);
		unsigned int m_id;
		Sprite* m_body;
		Node*	root_node;
	protected:
		

	};


}