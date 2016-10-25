#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Entity : public Ref
{
public:
	Entity();
	~Entity();

	bool init(void);
	static Entity* create(void);


};