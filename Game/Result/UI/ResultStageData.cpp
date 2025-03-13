// ================================================================ 
// ファイル名 : ResultStageData.cpp
// 作成者 : 景山碧天
// 説明 :  リザルトでのステージ名表示
// ================================================================
#include"pch.h"
#include"ResultStageData.h"
#include"Base/Scene/Scene.h"
#include"Game/GameManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">所属キャンバス</param>
ResultStageData::ResultStageData(Canvas* canvas):UserInterface(canvas)
{
	using namespace DirectX::SimpleMath;
	SetActive(false);
	//ボード生成
	UserInterface* board = GetScene()->AddObject<UserInterface>(canvas, "ResultBoard",2);
	board->SetPosition(Vector2(330, 155));
	board->SetSize(Vector2(660, 150));
	//ステージ番号を取得
	std::pair<int,int> stageNum = GameManager::GetInstance()->GetStageNum();
	//大番号生成
	UserInterface* number = GetScene()->AddObject<UserInterface>(canvas, "Numbers", 3);
	number->SetClipRange(Vector4(stageNum.first / 10.0f, 0, 0.1f, 1.0f));
	number->SetPosition(Vector2(180, 155));
	//小番号生成
	number = GetScene()->AddObject<UserInterface>(canvas, "Numbers", 3);
	number->SetClipRange(Vector4(stageNum.second / 10.0f, 0, 0.1f, 1.0f));
	number->SetPosition(Vector2(380, 155));
	//ハイフン生成
	UserInterface* hyphen = GetScene()->AddObject<UserInterface>(canvas, "Hyphen", 3);
	hyphen->SetPosition(Vector2(280, 155));
}
