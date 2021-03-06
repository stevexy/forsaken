///
/// 用于控制lua脚本中对象的更新
/// lua脚本通过这个类来获取rendercomponent
/// rendercomponent里面包含sprite
/// lua脚本通过改变rendercomponent的属性，达到控制sprite动画之类的行为
///

#pragma once
#include "cocos2d.h"
//#include "base/CCScriptSupport.h"
#include "../EntityCom/entityManager.h"
#include <map>

using namespace std;
using namespace cocos2d;



namespace xyGame {
	typedef map<unsigned int, Entity *> ENT_MAP;

	class RenderController : public Ref
	{
		static ENT_MAP entity_map;
		static unsigned int ent_id;

	public:
		static RenderController* renderControllerObj;
		static RenderController* getInstance();
		//	struct Ent;
		RenderController();
		~RenderController();

		
		bool init(void);
		static RenderController* create(void);

		void update(float fixedDelta);
		void animate(double delta, double tickPercent);

		Entity* createEntity();

	protected:
#if CC_ENABLE_SCRIPT_BINDING
		ccScriptType _scriptType;         ///< type of script binding, lua or javascript 
										///只是用来在消息传递中，或者会调中分清lua 还是 javascript
#endif

	};
	
}

int lua_register_cocos2dx_RenderController(lua_State* tolua_S);
int lua_register_cocos2dx_Entity(lua_State* tolua_S);