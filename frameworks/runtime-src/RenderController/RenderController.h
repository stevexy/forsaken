///
/// ���ڿ���lua�ű��ж���ĸ���
/// lua�ű�ͨ�����������ȡrendercomponent
/// rendercomponent�������sprite
/// lua�ű�ͨ���ı�rendercomponent�����ԣ��ﵽ����sprite����֮�����Ϊ
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