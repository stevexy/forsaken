///
/// ���ڿ���lua�ű��ж���ĸ���
/// lua�ű�ͨ�����������ȡrendercomponent
/// rendercomponent�������sprite
/// lua�ű�ͨ���ı�rendercomponent�����ԣ��ﵽ����sprite����֮�����Ϊ
///

#pragma once
#include "cocos2d.h"
//#include "base/CCScriptSupport.h"


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
protected:
#if CC_ENABLE_SCRIPT_BINDING
	cocos2d::ccScriptType _scriptType;         ///< type of script binding, lua or javascript
#endif
};

int lua_register_cocos2dx_RenderController(lua_State* tolua_S);