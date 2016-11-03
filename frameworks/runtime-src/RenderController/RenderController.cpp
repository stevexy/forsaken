#include "RenderController.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

namespace xyGame {

	RenderController* RenderController::renderControllerObj = nullptr;
	unsigned int RenderController::ent_id(1);
	ENT_MAP RenderController::entity_map;
	typedef pair<unsigned int, Entity*> ENT_PAIR;


	RenderController * RenderController::getInstance()
	{
		if (!renderControllerObj)
		{
			return create();
		}
		return renderControllerObj;
	}

	RenderController::RenderController()
		//	: _messageBoxService(nullptr)
	{
	#if CC_ENABLE_SCRIPT_BINDING
		ScriptEngineProtocol* engine = ScriptEngineManager::getInstance()->getScriptEngine();
		_scriptType = engine != nullptr ? engine->getScriptType() : kScriptTypeNone;
	#endif
	}

	RenderController::~RenderController()
	{
		//	CC_SAFE_DELETE(_menuService);
		for (ENT_MAP::iterator it = entity_map.begin(); it != entity_map.end(); ++it)
		{
			it->second->release();
		}
		entity_map.clear();
		Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(RenderController::update), this);		
	}

	Entity* RenderController::createEntity()
	{
		Entity *ent = Entity::create();
		entity_map.insert(ENT_PAIR(ent->get_eid(), ent));
		ent->retain();
		return ent;

	}

	bool RenderController::init(void)
	{
		Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(RenderController::update), this, 0, false);
		return true;
	}

	RenderController * RenderController::create(void)
	{
		RenderController *rcobj = new (std::nothrow) RenderController();
		rcobj->init();
		rcobj->autorelease();
		renderControllerObj = rcobj;
		return rcobj;
	}

	void RenderController::update(float fixedDelta)
	{
		for (ENT_MAP::iterator it = entity_map.begin(); it != entity_map.end(); ++it)
		{
			it->second->update(fixedDelta);
		}
	}

	void RenderController::animate(double delta, double tickPercent)
	{
	}

	int lua_cocos2dx_RenderComponent_constructor(lua_State* tolua_S)
	{
		int argc = 0;

		RenderController* cobj = nullptr;
		bool ok = true;

	#if COCOS2D_DEBUG >= 1
		tolua_Error tolua_err;
	#endif

		argc = lua_gettop(tolua_S) - 1;
		if (argc == 0)
		{
			if (!ok)
			{
				tolua_error(tolua_S, "invalid arguments in function 'lua_cocos2dx_RenderComponent_constructor'", nullptr);
				return 0;
			}
			cobj = new RenderController();
			cobj->autorelease();
			int ID = (int)cobj->_ID;
			int* luaID = &cobj->_luaID;
			toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj, "cc.RenderController");
			return 1;
		}
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderController", argc, 0);
		return 0;

	#if COCOS2D_DEBUG >= 1
		tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_RenderComponent_constructor'.", &tolua_err);
	#endif

		return 0;
	}

	int lua_cocos2dx_RenderComponent_create(lua_State* tolua_S)
	{
		int argc = 0;
		bool ok = true;
	#if COCOS2D_DEBUG >= 1
		tolua_Error tolua_err;
	#endif

	#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertable(tolua_S, 1, "cc.RenderController", 0, &tolua_err)) goto tolua_lerror;
	#endif

		argc = lua_gettop(tolua_S) - 1;
		do
		{
			if (argc == 0)
			{
				RenderController* ret = RenderController::create();
				object_to_luaval<RenderController>(tolua_S, "cc.RenderController", (RenderController*)ret);
				return 1;
			}
		} while (0);
		ok = true;
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.RenderController:create", argc, 0);
		return 0;
	#if COCOS2D_DEBUG >= 1
		tolua_lerror:
		tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_RenderComponent_create'.", &tolua_err);
	#endif
		return 0;
	}

	int lua_cocos2dx_Entity_getSprite(lua_State* tolua_S)
	{
		int argc = 0;
		Entity* cobj = nullptr;
		bool ok = true;

	#if COCOS2D_DEBUG >= 1
		tolua_Error tolua_err;
	#endif


	#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S, 1, "cc.Entity", 0, &tolua_err)) goto tolua_lerror;
	#endif

		cobj = (Entity*)tolua_tousertype(tolua_S, 1, 0);

	#if COCOS2D_DEBUG >= 1
		if (!cobj)
		{
			tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_Entity_getSprite'", nullptr);
			return 0;
		}
	#endif

		argc = lua_gettop(tolua_S) - 1;
		if (argc == 0)
		{
			Sprite* ret = cobj->get_sprite();
			//		lua_settop(tolua_S, 1);
			object_to_luaval<Sprite>(tolua_S, "cc.Sprite", (cocos2d::Sprite*)ret);
	//		tolua_pushnumber(tolua_S, (lua_Number)ret);
			return 1;
		}
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Entity:getSprite", argc, 1);
		return 0;

	#if COCOS2D_DEBUG >= 1
		tolua_lerror:
		tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_Entity_getSprite'.", &tolua_err);
	#endif

		return 0;
	}

	int lua_cocos2dx_Entity_getRoot(lua_State* tolua_S)
	{
		int argc = 0;
		Entity* cobj = nullptr;
		bool ok = true;

#if COCOS2D_DEBUG >= 1
		tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S, 1, "cc.Entity", 0, &tolua_err)) goto tolua_lerror;
#endif

		cobj = (Entity*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
		if (!cobj)
		{
			tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_Entity_getRoot'", nullptr);
			return 0;
		}
#endif

		argc = lua_gettop(tolua_S) - 1;
		if (argc == 0)
		{
			Node* ret = cobj->get_root();
			//		lua_settop(tolua_S, 1);
			object_to_luaval<Sprite>(tolua_S, "cc.Node", (cocos2d::Sprite*)ret);
			//		tolua_pushnumber(tolua_S, (lua_Number)ret);
			return 1;
		}
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Entity:getRoot", argc, 1);
		return 0;

#if COCOS2D_DEBUG >= 1
		tolua_lerror:
					tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_Entity_getRoot'.", &tolua_err);
#endif

					return 0;
	}

	int lua_cocos2dx_Entity_setDirection(lua_State* tolua_S)
	{
		int argc = 0;
		Entity* cobj = nullptr;
		bool ok = true;

	#if COCOS2D_DEBUG >= 1
		tolua_Error tolua_err;
	#endif


	#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S, 1, "cc.Entity", 0, &tolua_err)) goto tolua_lerror;
	#endif

		cobj = (Entity*)tolua_tousertype(tolua_S, 1, 0);

	#if COCOS2D_DEBUG >= 1
		if (!cobj)
		{
			tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_Entity_setDirection'", nullptr);
			return 0;
		}
	#endif

		argc = lua_gettop(tolua_S) - 1;
		if (argc == 1)
		{
			double arg0;

			ok &= luaval_to_number(tolua_S, 2, &arg0, "cc.Entity:setDirection");
			if (!ok)
			{
				tolua_error(tolua_S, "invalid arguments in function 'lua_cocos2dx_Entity_setDirection'", nullptr);
				return 0;
			}
			cobj->set_direction(arg0);
			lua_settop(tolua_S, 1);
			return 1;
		}
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setDirection", argc, 1);
		return 0;

	#if COCOS2D_DEBUG >= 1
		tolua_lerror:
		tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_Entity_setDirection'.", &tolua_err);
	#endif

		return 0;

	}

	int lua_cocos2dx_RenderComponent_createEntity(lua_State* tolua_S)
	//函数，创建一个game entity ，返回给脚本对象使用
	// Entity 里面有sprite ，还需要进一步返回entity里面的sprite
	{
		int argc = 0;
		RenderController* cobj = nullptr;
		bool ok = true;
	#if COCOS2D_DEBUG >= 1
		tolua_Error tolua_err;
	#endif

	#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertype(tolua_S, 1, "cc.RenderController", 0, &tolua_err)) goto tolua_lerror;
	#endif

		cobj = (RenderController*)tolua_tousertype(tolua_S, 1, 0);

	#if COCOS2D_DEBUG >= 1
		if (!cobj)
		{
			tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_RenderComponent_createEntity'", nullptr);
			return 0;
		}
	#endif

		argc = lua_gettop(tolua_S) - 1;
		do
		{
			if (argc == 0)
			{
				Entity* ret = cobj->createEntity();
				object_to_luaval<Entity>(tolua_S, "cc.Entity", (Entity*)ret);
				return 1;
			}
		} while (0);
		ok = true;
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.RenderController:createEntity", argc, 0);
		return 0;
	#if COCOS2D_DEBUG >= 1
		tolua_lerror:
		tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_RenderComponent_createEntity'.", &tolua_err);
	#endif
		return 0;
	}


	static int lua_cocos2dx_RenderController_finalize(lua_State* tolua_S)
	{
		printf("luabindings: finalizing LUA object (RenderController)");
		return 0;
	}

	int lua_cocos2dx_Entity_constructor(lua_State* tolua_S)
	{
		int argc = 0;

		Entity* cobj = nullptr;
		bool ok = true;

	#if COCOS2D_DEBUG >= 1
		tolua_Error tolua_err;
	#endif

		argc = lua_gettop(tolua_S) - 1;
		if (argc == 0)
		{
			if (!ok)
			{
				tolua_error(tolua_S, "invalid arguments in function 'lua_cocos2dx_Entity_constructor'", nullptr);
				return 0;
			}
			cobj = new Entity();
			cobj->autorelease();
			int ID = (int)cobj->_ID;
			int* luaID = &cobj->_luaID;
			toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj, "cc.Entity");
			return 1;
		}
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Entity", argc, 0);
		return 0;

	#if COCOS2D_DEBUG >= 1
		tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_Entity_constructor'.", &tolua_err);
	#endif

		return 0;
	}

	static int lua_cocos2dx_Entity_finalize(lua_State* tolua_S)
	{
		printf("luabindings: finalizing LUA object (Entity)");
		return 0;
	}

}

using namespace xyGame;

int lua_register_cocos2dx_RenderController(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, "cc.RenderController");
	tolua_cclass(tolua_S, "RenderController", "cc.RenderController", "cc.Ref", nullptr);
	tolua_beginmodule(tolua_S, "RenderController");
	tolua_function(tolua_S, "new", lua_cocos2dx_RenderComponent_constructor);
	tolua_function(tolua_S, "create", lua_cocos2dx_RenderComponent_create);
	tolua_function(tolua_S, "createEntity", lua_cocos2dx_RenderComponent_createEntity);
	tolua_endmodule(tolua_S);
	std::string typeName = typeid(RenderController).name();
	g_luaType[typeName] = "cc.RenderController";
	g_typeCast["RenderController"] = "cc.RenderController";
	return 1;
}

int lua_register_cocos2dx_Entity(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, "cc.Entity");
	tolua_cclass(tolua_S, "Entity", "cc.Entity", "cc.Ref", nullptr);
	tolua_beginmodule(tolua_S, "Entity");
	tolua_function(tolua_S, "new", lua_cocos2dx_Entity_constructor);
	tolua_function(tolua_S, "getSprite", lua_cocos2dx_Entity_getSprite);
	tolua_function(tolua_S, "getRoot", lua_cocos2dx_Entity_getRoot);
	tolua_function(tolua_S, "setDirection", lua_cocos2dx_Entity_setDirection);
	tolua_endmodule(tolua_S);
	std::string typeName = typeid(Entity).name();
	g_luaType[typeName] = "cc.Entity";
	g_typeCast["Entity"] = "cc.Entity";
	return 1;
}


