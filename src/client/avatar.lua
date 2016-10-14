local gamePlayer = class("Player", function()
    return cc.Sprite:create()
end)

function gamePlayer:ctor()
	self:onCreate()
end

function gamePlayer:onCreate()
    self.vel_x = 0
    self.vel_y = 0
	self.moving_action = 0
	local cache = cc.SpriteFrameCache:getInstance()
    for i = 1,3 do 
        local frame = cc.SpriteFrame:create( "res/101.png", cc.rect((i-1)*46, 0, 32, 36) )
        cache:addSpriteFrame(frame,string.format("walk_down_%d",i))
    end
    for i = 1,3 do 
        local frame = cc.SpriteFrame:create( "res/101.png", cc.rect((i-1)*46, 36, 32, 36) )
        cache:addSpriteFrame(frame,string.format("walk_right_%d",i))
    end
    for i = 1,3 do 
        local frame = cc.SpriteFrame:create( "res/101.png", cc.rect((i-1)*46, 72, 32, 36) )
        cache:addSpriteFrame(frame,string.format("walk_up_%d",i))
    end 
    for i = 1,3 do 
        local frame = cc.SpriteFrame:create( "res/101.png", cc.rect((i-1)*46, 108, 32, 36) )
        cache:addSpriteFrame(frame,string.format("walk_left_%d",i))
    end
end


function gamePlayer:update(dt)
    --如果是grid的话，便每次移动一个grid
    local speed = 100
    local x,y = self:getPosition()
    if self.vel_x > 0 then
        self:Walk("right")
	    self:Move(x+speed*dt,y,dt)
    elseif self.vel_x < 0 then
        self:Walk("left")
	    self:Move(x-speed*dt,y,dt)
    elseif self.vel_y > 0 then
        self:Walk("up")
	    self:Move(x,y+speed*dt,dt)
    elseif self.vel_y < 0 then
        self:Walk("down")
	    self:Move(x,y-speed*dt,dt)
    end
end

function gamePlayer:Walk(position)
	print ('runaction',position)
    if self.last_action == position then
        return
    else
        self.last_action = position
    end


	local cache = cc.SpriteFrameCache:getInstance()
-- 	local s = cc.Director:getInstance():getWinSize()
--  self:setPosition( cc.p( (s.width/5)*3, (s.height/3)*1) )

    local animFrames = {}
    for i = 1,3 do
        local frame = cache:getSpriteFrame(string.format("walk_%s_%d",position,i))
        animFrames[i] = frame
    end
	self:stopAllActions()
    local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
    self:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))
end

function gamePlayer:Move(destx,desty,step)
		local function ActionSequenceCallback1()  
			self.moving_action = 0
		end
		self.moving_action = 1
		local action = cc.Sequence:create(cc.MoveTo:create(0.2*step, cc.p(destx,desty)), 
			cc.CallFunc:create(ActionSequenceCallback1))
	    self:runAction(action)
end

function gamePlayer:isMoving()
    if self.moving_action then
    	return self.moving_action
    else
        return 0
    end
end

function gamePlayer:get_coord()	
end

return gamePlayer