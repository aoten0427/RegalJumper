// ================================================================ 
// ファイル名 : GameSound.h
// 作成者 : 景山碧天
// 説明 :  BGMの管理
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class Sound;

class GameSound :public Object
{
private:
	//タイトルサウンド
	Sound* m_titileSound;
	//プレイサウンド
	Sound* m_playSound;
public:
	//コンストラクタ
	GameSound(Scene* scene);
	//デストラクタ
	~GameSound()override = default;
	//シーン切り替え時イベント
	void LoadScene(Scene* scene) override;
};