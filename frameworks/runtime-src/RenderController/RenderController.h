///
/// ���ڿ���lua�ű��ж���ĸ���
/// lua�ű�ͨ�����������ȡrendercomponent
/// rendercomponent�������sprite
/// lua�ű�ͨ���ı�rendercomponent�����ԣ��ﵽ����sprite����֮�����Ϊ
///

#pragma once
class RenderController
{
public:
//	struct Ent;

	static void tick(double fixedDelta);
	static void animate(double delta, double tickPercent);
};
