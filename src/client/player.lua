local gamePlayer = class("Player",{})

function gamePlayer:ctor()
--	self:onCreate()
-- 暂时不要
end


function gamePlayer:setRC(render_controller)
    self.entity = render_controller:createEntity()
    self.entity:retain()
    
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

function gamePlayer:getSprite()
    return self.entity:getSprite()
end

function gamePlayer:update_direction()
    --如果是grid的话，便每次移动一个grid
    if self.vel_x > 0 then
        self:Walk("right")
    elseif self.vel_x < 0 then
        self:Walk("left")
    elseif self.vel_y > 0 then
        self:Walk("up")
    elseif self.vel_y < 0 then
        self:Walk("down")
    else
        self:Walk("idle")
    end
end

function gamePlayer:Walk(dir)
    if dir == 'left' then
    	self.entity:setDirection(1)
    elseif dir == 'right' then
    	self.entity:setDirection(2)
    elseif dir == 'up' then
    	self.entity:setDirection(3)
    elseif dir == 'down' then
    	self.entity:setDirection(4)
    elseif dir == 'idle' then
    	self.entity:setDirection(0)
    end
	local cache = cc.SpriteFrameCache:getInstance()
    local _spr = self.entity:getSprite()
    local position = 'idle'
    if dir ~= 'idle' then
        position = dir
    end
    local animFrames = {}
    for i = 1,3 do
        local frame = cache:getSpriteFrame(string.format("walk_%s_%d",dir,i))
        animFrames[i] = frame
    end
	_spr:stopAllActions()
    local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
    _spr:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))
end

function gamePlayer:get_coord()	
end

return gamePlayer