// ================================================================ 
// ファイル名 : GameFade.h
// 作成者 : 景山碧天
// 説明 :  ゲームの基本フェード
// ================================================================

#pragma once
#include"Base/Fade/Fade.h"

class Sequence;
template<typename...Args>
class Subject;

class GameFade :public Fade
{
private:
	//表示位置
	DirectX::SimpleMath::Vector2 m_position;
	//移動に使うSequence
	Sequence* m_sequence;
	//クローズした際の処理
	std::function<void()> m_closeFunction;
	//フェード終了通知
	Subject<>* m_finishSubject;
public:
	//コンストラクタ
	GameFade(Canvas* canvas);
	//デストラクタ
	~GameFade()override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
	//フェード開始
	void Start(std::function<void()> function = nullptr);
};