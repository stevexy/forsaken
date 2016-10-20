///
/// 用于控制lua脚本中对象的更新
/// lua脚本通过这个类来获取rendercomponent
/// rendercomponent里面包含sprite
/// lua脚本通过改变rendercomponent的属性，达到控制sprite动画之类的行为
///

#pragma once
#include "cocos2d.h"



class RenderController: public cocos2d::Ref
{
public:
//	struct Ent;
	RenderController();
	~RenderController();

	bool init(void);
	static RenderController* create(void);

	static void tick(double fixedDelta);
	static void animate(double delta, double tickPercent);
	int testGetID();
};

int lua_register_cocos2dx_RenderController(lua_State* tolua_S);