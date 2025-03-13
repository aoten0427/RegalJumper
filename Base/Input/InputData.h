#pragma once

using AxisState = DirectX::SimpleMath::Vector2;

enum KeyState
{
	Free = 1 << 0,		// ‰½‚à‰Ÿ‚µ‚Ä–³‚¢
	Press = 1 << 1,		// ‰Ÿ‚µ‚½uŠÔ
	Hold = 1 << 2,		// ‰Ÿ‚µ‚Ä‚¢‚éŠÔ
	Release = 1 << 3	// —£‚µ‚½uŠÔ
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