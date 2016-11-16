local gamePlayer = class("Player",{})

function gamePlayer:ctor()
--	self:onCreate()
-- 暂时不要
    self.last_action = 'down'
    self.attacking = false
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

    self.weapon = cc.Sprite:create( "res/sword1.png")
    local root = self:getRoot()
    root:addChild(self.weapon, 4, 0)
    self.weapon:setAnchorPoint({0.5,0})
    --self.weapon:setScale(2)
end

function gamePlayer:getSprite()
    return self.entity:getSprite()
end

function gamePlayer:getRoot()
    return self.entity:getRoot()
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

function gamePlayer:attack()
    if self.attacking == true then
        return
    end
    local function action_done()
        self.attacking = false
        self:setWeaponPos(self.last_action)
    end
    self.attacking = true
    local angle = 180
    if table.keyof({"left","up"},self.last_action) then
        angle = -180
    end
    local actionBy = cc.RotateBy:create(0.1 , angle)
    local actionByBack = actionBy:reverse()
    local callfunc = cc.CallFunc:create(action_done)
    self.weapon:runAction(cc.Sequence:create(actionBy, actionByBack, callfunc))
end



function gamePlayer:setWeaponPos(dir)
    local bb = self.weapon:getContentSize()
    print ('sword bounding box',bb.width,bb.height)
    if dir == 'left' then
    	self.weapon:setPosition( cc.p( -10+bb.width/2,0 ) )
        self.weapon:setLocalZOrder(2)
    elseif dir == 'right' then
    	self.weapon:setPosition( cc.p( -8+bb.width/2,-10 ) )
        self.weapon:setLocalZOrder(4)
    elseif dir == 'up' then
    	self.weapon:setPosition( cc.p( 6+bb.width/2,-6 ) )
        self.weapon:setLocalZOrder(2)
    elseif dir == 'down' then
    	self.weapon:setPosition( cc.p( -10-bb.width/2,-10 ) )
        self.weapon:setLocalZOrder(4)
    elseif dir == 'idle' then
    	self.weapon:setPosition( cc.p( -10-bb.width/2,-10 ) )
        self.weapon:setLocalZOrder(4)
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
    else
        return
    end
    
    if self.last_action ~= position then
        self.last_action = position
    else
        return
    end

    self:setWeaponPos(position)

    local animFrames = {}
    for i = 1,3 do
        local frame = cache:getSpriteFrame(string.format("walk_%s_%d",position,i))
        animFrames[i] = frame
    end
	_spr:stopAllActions()
    local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
    _spr:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))
end

function gamePlayer:get_coord()	
end

return gamePlayer