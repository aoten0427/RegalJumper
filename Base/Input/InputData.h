#pragma once

using AxisState = DirectX::SimpleMath::Vector2;

enum KeyState
{
	Free = 1 << 0,		// ���������Ė���
	Press = 1 << 1,		// �������u��
	Hold = 1 << 2,		// �����Ă����
	Release = 1 << 3	// �������u��
};


class InputData
{
public:
	enum class KEY
	{
		A,B,C,D,E,F,G,H,I,J,K,L,M,
		N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
		Up,Down,Left,Right,Space,
		Enter,Escape,RClick,LClick
	};
};