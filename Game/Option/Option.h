// ================================================================ 
// ファイル名 : Option.h
// 作成者 : 景山碧天
// 説明 :  オプション
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"
#include"Base/Scene/Scene.h"


class Tween;
template<typename...Args>
class Subject;
class OptionContents;
class OptionExit;


class Option :public UserInterface
{
private:
	static constexpr int SELECT_NUM = 3;

	//選択肢
	enum class SELECT
	{
		BGM,
		SE,
		SENSITIVITY
	};
public:
	float GetSensitivity() const { return m_sensitivity; }
private:
	//事前状態
	Scene::State m_oldSceneState;
	//大きさ
	DirectX::SimpleMath::Vector2 m_size;
	//開閉用Tween
	Tween* m_tween;
	//開いた時の時のSubject
	Subject<>* m_openSubject;
	//閉じたときのSubject
	Subject<>* m_closeSubject;
	//変更内容
	OptionContents* m_contents[SELECT_NUM];
	//初期パーセント格納
	float m_initialParcent[SELECT_NUM];
	//退出ボタン
	OptionExit* m_exitButton;
	//感度
	float m_sensitivity;
public:
	//コンストラクタ
	Option(Canvas* canvas);
	~Option()override = default;
	//アップデート
	void ObjectUpdate(float deltatime)override;
	//終了処理
	void Finalize()override;
	//開く
	void Open();
	//閉じる
	void Close();
private:
	void LoadData();
	void WriteData();
};