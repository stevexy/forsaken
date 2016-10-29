#pragma once
#include "cocos2d.h"

using namespace cocos2d;

namespace xyGame {
	class Entity : public Ref
	{
	public:
		static unsigned int EID;
		Entity();
		~Entity();

		unsigned int get_eid() { return m_id; }
		int do_test() { return 111; }
		bool init(void);
		static Entity* create(void);
		unsigned int m_id;
		Sprite* m_body;
	protected:
		

	};


}