// ================================================================ 
// ファイル名 : ResultStageData.h
// 作成者 : 景山碧天
// 説明 :  リザルトでのステージ名表示
// ================================================================
#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class ResultStageData :public UserInterface
{
private:
public:
	//コンストラクタ
	ResultStageData(Canvas* canvas);
	//デストラクタ
	~ResultStageData() override = default;
};