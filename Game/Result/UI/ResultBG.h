// ================================================================ 
// ファイル名 : ResultBG.h
// 作成者 : 景山碧天
// 説明 :  リザルト背景
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"

class ResultBG :public UserInterface
{
private:
	//四角
	std::vector<UserInterface*> m_quads;
	//四角の色
	std::vector<DirectX::SimpleMath::Vector4> m_quadsColor;
	//四角の出現時間
	std::vector<float> m_openTime;
	//タイマー
	float m_timer;
	//ループセット用フラグ
	bool m_flag;
public:
	//コンストラクタ
	ResultBG(Canvas* canvas);
	//デストラクタ
	~ResultBG()override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
private:
	//データ読み込み
	void LoadData();
	//ループをセット
	void LoopSet();

};