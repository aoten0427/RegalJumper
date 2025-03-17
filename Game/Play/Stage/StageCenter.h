// ================================================================ 
// ファイル名 : StageCenter
// 作成者 : 景山碧天
// 説明 :  プレイ画面に配置するオブジェクトを管理
// ================================================================

#pragma once
#include"Base/Object/Object.h"
class PlayerCenter;

class StageCenter :public Object
{
private:
	PlayerCenter* m_playerCenter;
public:
	//コンストラクタ
	StageCenter(Scene* scene,PlayerCenter* playercenter);
	//デストラクタ
	~StageCenter()override = default;
private:
	//データ読み込み
	void LoadData();
};
