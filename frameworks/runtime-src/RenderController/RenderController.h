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

	static void tick(double fixedDelta);
	static void animate(double delta, double tickPercent);
};
