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

		bool init(void);
		static Entity* create(void);
		unsigned int m_id;
		Sprite* m_body;
	protected:
		

	};


}