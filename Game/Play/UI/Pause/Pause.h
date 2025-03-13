// ================================================================ 
// ファイル名 : Pause.h
// 作成者 : 景山碧天
// 説明 :  プレイ画面ポーズ
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"
#include"Base/Scene/Scene.h"

template<typename...Args>
class Subject;
class PauseButton;
class QuitPage;

class Pause :public UserInterface
{
private:
	//openフラグ
	bool m_isOpen;
	//白背景以外のUIの親
	Object* m_UIBase;
	//ベース
	UserInterface* m_base;
	//退出ページ
	QuitPage* m_quitPage;
	//オープンサブジェクト
	Subject<>* m_openSubject;
	//クローズサブジェクト
	Subject<>* m_closeSubject;
	//前回のシーンステート
	Scene::State m_oldSceneState;
public:
	//コンストラクタ
	Pause(Canvas* canvas);
	//デストラクタ
	~Pause()override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
private:
	//開く
	void Open();
	//閉じる
	void Close();
};