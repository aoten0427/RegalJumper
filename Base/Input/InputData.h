#pragma once

using AxisState = DirectX::SimpleMath::Vector2;

enum KeyState
{
	Free = 1 << 0,		// 何も押して無い
	Press = 1 << 1,		// 押した瞬間
	Hold = 1 << 2,		// 押している間
	Release = 1 << 3	// 離した瞬間
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