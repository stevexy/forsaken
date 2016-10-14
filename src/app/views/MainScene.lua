local Avatar = require("client.avatar")
local ControlLayer = require("client.stick.stick")
local math = require("math")

local MainScene = class("MainScene", cc.load("mvc").ViewBase)


local kTagTileMap = 1


-- local function createTileDemoLayer()
--     local layer = cc.Layer:create()
	
--     local function onTouchesMoved(touches, event )
--         local diff = touches[1]:getDelta()
--         local node = layer:getChildByTag(kTagTileMap)
--         local currentPosX, currentPosY= node:getPosition()
--         node:setPosition(cc.p(currentPosX + diff.x, currentPosY + diff.y))
--     end

-- --    local listener = cc.EventListenerTouchAllAtOnce:create()
-- --    listener:registerScriptHandler(onTouchesMoved,cc.Handler.EVENT_TOUCH_ENDED )	--���������ƶ���
-- --    local eventDispatcher = layer:getEventDispatcher()
-- --    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)
-- --
--     return layer
-- end

function MainScene:createController()
	local controller = ControlLayer:create()
	self:scheduleUpdateWithPriorityLua(function(...) self:update(...) end,0)
	return controller
end

--通过定时器update是一种思路，逐帧检测control的输入来决定角色的动作
--关于动作，需要一个动作匹配器，根据方向和速度匹配速度，如果处于攻击或硬直，就停止移动
--碰撞检测
function MainScene:update(dt)
	if self.player == nil then
		return
	end
	self.player:update(dt)

	-- if self.controller.direction then
		
	-- 	local x,y = self.player:getPosition()
	-- 	if self.player:isMoving() ~= 0 then
	-- 		return
	-- 	end

	-- 	if self.controller._beactive == false or self.controller.distance < 32 then
	-- 		return
	-- 	end
	-- 	--通过摇杆的方向直接设置速度是不好的
	-- 	--应该是player主动去读取摇杆的位置来设置速度
	-- 	--并在ticker里面移动
	-- 	if math.abs(self.controller.direction.x) > math.abs(self.controller.direction.y) then
	-- 		if self.controller.direction.x > 0 then
	-- 			self.player:Walk("right")
	-- 			self.player:Move(x+16,y,0.5)
	-- 		else
	-- 			self.player:Walk("left")
	-- 			self.player:Move(x-16,y,0.5)
	-- 		end
	-- 	else
	-- 		if self.controller.direction.y > 0 then
	-- 			self.player:Walk("up")
	-- 			self.player:Move(x,y+16,0.5)
	-- 		else
	-- 			self.player:Walk("down")
	-- 			self.player:Move(x,y-16,0.5)
	-- 		end
	-- 	end
	-- end
end

function MainScene:onCreate()
    -- add background image
    display.newSprite("HelloWorld.png")
        :move(display.center)
        :addTo(self)

    cc.Label:createWithSystemFont("Hello World", "Arial", 40)
        :move(display.cx, display.cy + 200)
        :addTo(self)
	
	print(string.format("seayoung create controller"))
	local xcontrol = self:createController()
	xcontrol:setTouchEnabled(true)
	self.controller = xcontrol

	local layer = cc.Layer:create()
	--layer:setTouchEnabled(true)
	layer:addTo(self)
    local xmap = cc.TMXTiledMap:create("res/firstmap.tmx")
    layer:addChild(xmap, 0, kTagTileMap)
    
	xcontrol:addTo(self)
    local _player = Avatar:create()
    self.player = _player
    --xmap:setPosition(cc.p(0,0))
    _player:Walk("right")
    
    local layer_terrain = xmap:getLayer('terrain')
    local layer_block = xmap:getLayer('block')
    xmap:addChild(_player, 5, 0)
    --print("seayoung test tilemap",xmap:getTileSize().height)
    local tsize = layer_terrain:getLayerSize()
   	local m_x = (tsize.width+1)*xmap:getTileSize().width/2
   	local m_y = (tsize.height+1)*xmap:getTileSize().height/2
    print("seayoung test tilemap",tsize.height,tsize.width)
    _player:setPosition( cc.p( m_x,m_y ) )
    
	local function tileCoordForPosition(_mmap,position)
	    local x = math.floor(position.x / _mmap:getTileSize().width)
	    local y = math.floor(((_mmap:getMapSize().height * _mmap:getTileSize().height) - position.y) / _mmap:getTileSize().height)
	    return cc.p(x, y)
	end

	local function onKeyPress(keycode, event)
		if keycode == cc.KeyCode.KEY_A then
			self.player.vel_x = -1
			self.player.vel_y = 0
		elseif keycode == cc.KeyCode.KEY_D then
			self.player.vel_x = 1
			self.player.vel_y = 0
		elseif keycode == cc.KeyCode.KEY_S then
			self.player.vel_y = -1
			self.player.vel_x = 0
		elseif keycode == cc.KeyCode.KEY_W then
			self.player.vel_y = 1
			self.player.vel_x = 0
		end
	end

	local function onKeyReleased(keycode, event)
	end

    local listenerKeyboard=cc.EventListenerKeyboard:create()
    listenerKeyboard:registerScriptHandler(onKeyPress,cc.Handler.EVENT_KEYBOARD_PRESSED)
	listenerKeyboard:registerScriptHandler(onKeyReleased, cc.Handler.EVENT_KEYBOARD_RELEASED)
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithFixedPriority(listenerKeyboard, 1);

    -- xmap:getTileSize().width/2+100, xmap:getTileSize().height/2+100) )
	--xmap:setScale(2)		--setScale֮���жϵ���������Ҳ�ı���
    local function onTouchesEnded(touches, event )
    	if _player:isMoving()==1 then
    		return
    	end
        local p = touches[1]:getLocation()
        
        local pos = layer_terrain:convertToNodeSpace(p)
        --pos����Ϊ��ͼ����layer������
        --Ҫͨ�����������õ�������grid
        -- �л���player���ڵ���һ������ȷ
        --local desx = math.floor((pos.x/xmap:getTileSize().width))*xmap:getTileSize().width+xmap:getTileSize().width/2
        --local desy = math.floor((pos.y/xmap:getTileSize().height))*xmap:getTileSize().height + xmap:getTileSize().height/2
       	
       	local x,y = _player:getPosition()
 		local diffx = pos.x - x
		local diffy = pos.y - y      	
       	local desx = x
       	local desy = y
       	if (math.abs(diffx) > math.abs(diffy)) then
       		if diffx > 0 then--�����ƶ�
       			desx = x + xmap:getTileSize().width
       		else
       			desx = x - xmap:getTileSize().width
       		end
       	else
       		if diffy > 0 then--�����ƶ�
       			desy = y + xmap:getTileSize().height
       		else
       			desy = y - xmap:getTileSize().height
       		end
       	end
       	
       	local touchTileCoord = tileCoordForPosition(xmap,cc.p(desx,desy))
       	

		local step = 0
		local dgridx = math.floor((pos.x/xmap:getTileSize().width))
		local dgridy = math.floor((pos.y/xmap:getTileSize().height))
		local ogridx = math.floor((x/xmap:getTileSize().width))
		local ogridy = math.floor((y/xmap:getTileSize().height))
		
		
	    local tileCoord = tileCoordForPosition(xmap,cc.p(desx,desy))
	    local tileGid = layer_block:getTileGIDAt(tileCoord)
	    if (tileGid) then
	        local properties = xmap:getPropertiesForGID(tileGid)
	        if (properties) then
	            local collision = properties["collide"]
	            if ("True" == collision) then
	                return
	            end
	        end
	    end

		if (math.abs(diffx) > math.abs(diffy)) then
				step = math.abs(dgridx-ogridx)
		        --print(string.format("seayoung test tilemap %d,[%d %d]",step,desx,desy))
		        if diffx >0 then
		            _player:Walk("right")
		            _player:Move(desx,y,0.5)
		        else
		            _player:Walk("left")
		            _player:Move(desx,y,0.5)
		        end
		else
				step = math.abs(dgridy-ogridy)
				--print(string.format("seayoung test tilemap %d,[%d %d]",step,desx,desy))
                if diffy >0 then
		            _player:Walk("up")
		            _player:Move(x,desy,0.5)
		        else
		            _player:Walk("down")
		            _player:Move(x,desy,0.5)
		        end		    
		end
	end

--    local listener = cc.EventListenerTouchAllAtOnce:create()
--    listener:registerScriptHandler(onTouchesEnded,cc.Handler.EVENT_TOUCHES_BEGAN  )	--���������ƶ���
--    local eventDispatcher = layer:getEventDispatcher()
--    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

end
return MainScene
