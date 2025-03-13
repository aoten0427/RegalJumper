// ================================================================ 
// ファイル名 : SelectArrow.h
// 作成者 : 景山碧天
// 説明 :  ステージ選択矢印
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/Button.h"

template<typename...Args>
class Subject;
template<typename...Args>
class Observer;
class Sound;

class SelectArrow :public Button
{
private:
	//反転確認
	bool m_inversion;
	//ポジション
	DirectX::SimpleMath::Vector2 m_position;
	//クリック時通知
	Subject<>* m_selectSubject;
	//ステージ変更オブザーバー
	Observer<>* m_observer;
	//サウンド
	Sound* m_sound;
public:
	//コンストラクタ
	SelectArrow(Canvas* canvas, bool inversion = false);
	//デストラクタ
	~SelectArrow()override = default;
	//アップデート
	void ObjectUpdate(float deltatime);
	//マウス感知イベント
	void MouseWithinEvent(bool within);
	//左クリックイベント
	void LeftClickEvent(bool within);
private:
	//表示を判断
	void CheckView();
};