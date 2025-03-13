// ================================================================ 
// ファイル名 : HelpInfomation.h
// 作成者 : 景山碧天
// 説明 :  ヘルプ内容
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class Tween;

class HelpInfomation :public UserInterface
{
public:
	//ヘルプ内容
	enum class INFOMATION
	{
		SHOT,
		MOVE,
		JUMP,
		SHOT2
	};
private:
	//背景
	UserInterface* m_bg;
	//大きさ
	DirectX::SimpleMath::Vector2 m_size;
	//変化用Tween
	Tween* m_tween;
public:
	//コンストラクタ
	HelpInfomation(Canvas* canvas,INFOMATION infomation);
	//デストラクタ
	~HelpInfomation()override = default;
	//アップデート
	void ObjectUpdate(float deltatime);
	//開く
	void Open();
	//閉じる
	void Close();
};