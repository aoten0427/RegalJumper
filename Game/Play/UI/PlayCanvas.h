// ================================================================ 
// ファイル名 : PlayCanvas.h
// 作成者 : 景山碧天
// 説明 :  プレイシーンキャンバス
// ================================================================

#pragma once
#include"Game/GameCanvas.h"

template<typename...Args>
class Observer;
class Time;

class PlayCanvas :public GameCanvas
{
private:
	//リザルト遷移時オブザーバー
	Observer<>* m_finishObserver;
	//経過時間
	float m_gameTimer;
	//タイマー
	class Time* m_time;
public:
	//コンストラクタ
	PlayCanvas(Scene* scene);
	//デストラクタ
	~PlayCanvas()override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
};