
local VitrualController = class("VitrualController", cc.Layer)

function VitrualController:ctor(app, name)
    self.distance = 0
    self._beactive = false
    if self.onCreate then self:onCreate() end
end

function VitrualController:onTouchesEnded(touches, event )
    self:_deactive()
end

function VitrualController:onTouchesBegan(touches, event )
    self.start_pos = cc.p(touches[1]:getLocation())
	self:_active(self.start_pos)
end

function VitrualController:onTouchesMove(touches, event )
    local pos = cc.p(touches[1]:getLocation())
    local distance = cc.pGetDistance(self.start_pos,pos)
    local direction = cc.pNormalize(cc.pSub(pos,self.start_pos))
    self:_update(direction,distance)
end


function VitrualController:onCreate()
    self.joystick = cc.Sprite:create( "res/Joystick_03.png")
    self.joystick:setScale(0.2,0.2)
    self.joystick_bg = cc.Sprite:create( "res/Back_04.png")
    self.joystick_bg:setScale(0.3,0.3)
    self:addChild(self.joystick_bg)
    self:addChild(self.joystick)

    local listener = cc.EventListenerTouchAllAtOnce:create()
    
    listener:registerScriptHandler(function(...) self:onTouchesBegan(...) end,cc.Handler.EVENT_TOUCHES_BEGAN  )
    listener:registerScriptHandler(function(...) self:onTouchesEnded(...) end,cc.Handler.EVENT_TOUCHES_ENDED  )
    listener:registerScriptHandler(function(...) self:onTouchesMove(...) end,cc.Handler.EVENT_TOUCHES_MOVED  )
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

end

function VitrualController:_active(pos)
    self._beactive = true
    self.joystick:setPosition(pos)
    self.joystick_bg:setPosition(pos)
    self.joystick:setVisible(true)
    self.joystick_bg:setVisible(true)
end

function VitrualController:_deactive(pos)
    self._beactive = false
    self.joystick:setVisible(false)
    self.joystick_bg:setVisible(false)
end

function VitrualController:_update(direction,distance)
    --print("seayoung udpate",direction.x,direction.y,distance)
    self.direction = direction
    self.distance = distance
    local start = cc.p(self.joystick_bg:getPosition())
    if distance < 32 then
        self.joystick:setPosition(cc.pAdd(start , (cc.pMul(direction ,distance))))
    else if distance > 96 then
        self.joystick:setPosition(cc.pAdd(start , (cc.pMul(direction ,64))))
    else
        self.joystick:setPosition(cc.pAdd(start , (cc.pMul(direction ,32))))
    end
end

end

return VitrualController

