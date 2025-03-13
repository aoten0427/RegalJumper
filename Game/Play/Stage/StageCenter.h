// ================================================================ 
// ファイル名 : StageCenter
// 作成者 : 景山碧天
// 説明 :  プレイ画面に配置するオブジェクトを管理
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class StageCenter :public Object
{
private:
public:
	//コンストラクタ
	StageCenter(Scene* scene);
	//デストラクタ
	~StageCenter()override = default;
private:
	//データ読み込み
	void LoadData();
};
