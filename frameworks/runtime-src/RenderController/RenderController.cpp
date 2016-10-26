#include "RenderController.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

namespace xyGame {
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

	}

	Entity * RenderController::createEntity()
	{
		Entity *ent = Entity::create();
		

		return ent;

	}

	bool RenderController::init(void)
	{
		return true;
	}

	RenderController * RenderController::create(void)
	{
		RenderController *animation = new (std::nothrow) RenderController();
		animation->init();
		animation->autorelease();

		return animation;
	}

	void RenderController::tick(double fixedDelta)
	{
	}

	void RenderController::animate(double delta, double tickPercent)
	{
	}

	int RenderController::testGetID()
	{
		return 101;
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
	int lua_cocos2dx_RenderComponent_getTestID(lua_State* tolua_S)
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
			tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_RenderComponent_getTestID'", nullptr);
			return 0;
		}
#endif

		argc = lua_gettop(tolua_S) - 1;
		if (argc == 0)
		{
			int ret = cobj->testGetID();
			//		lua_settop(tolua_S, 1);
			tolua_pushnumber(tolua_S, (lua_Number)ret);
			return 1;
		}
		luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:testGetID", argc, 1);
		return 0;

#if COCOS2D_DEBUG >= 1
		tolua_lerror:
					tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_RenderComponent_getTestID'.", &tolua_err);
#endif

					return 0;
	}


	static int lua_cocos2dx_RenderController_finalize(lua_State* tolua_S)
	{
		printf("luabindings: finalizing LUA object (RenderController)");
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
	tolua_function(tolua_S, "testGetID", lua_cocos2dx_RenderComponent_getTestID);
	tolua_function(tolua_S, "create", lua_cocos2dx_RenderComponent_create);
	tolua_endmodule(tolua_S);
	std::string typeName = typeid(RenderController).name();
	g_luaType[typeName] = "cc.RenderController";
	g_typeCast["RenderController"] = "cc.RenderController";
	return 1;
}