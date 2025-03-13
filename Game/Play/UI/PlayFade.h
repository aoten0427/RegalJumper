// ================================================================ 
// ファイル名 : PlayFade.h
// 作成者 : 景山碧天
// 説明 :  プレイシーンリセット用フェード
// ================================================================

#pragma once
#include"Base/Fade/Fade.h"

class Sequence;


class PlayFade :public Fade
{
private:
	//表示位置
	DirectX::SimpleMath::Vector2 m_position;
	//移動に使うSequence
	Sequence* m_sequence;
	//クローズした際の処理
	std::function<void()> m_closeFunction;
public:
	//コンストラクタ
	PlayFade(Canvas* canvas);
	//デストラクタ
	~PlayFade() override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
	//フェード開始
	void Start(std::function<void()> function = nullptr);
};