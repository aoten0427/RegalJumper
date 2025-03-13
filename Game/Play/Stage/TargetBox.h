// ================================================================ 
// ファイル名 : TargetBox.h
// 作成者 : 景山碧天
// 説明 :  移動に使うターゲットオブジェクト
// ================================================================
#pragma once
#include"Base/Object/Object.h"

class Model3D;
class Camera;
class RenderPrimitive;
class Target;
class TargetMark;
class Tween;

class TargetBox :public Object
{
private:
	//状態
	enum  class State
	{
		CLOSE,
		OPEN,
		MOVE
	};
public:
	//タグ取得
	ObjectTag GetTag() { return ObjectTag::TargetBox; };
private:
	//メインモデル
	Model3D* m_mainModel;
	//サブモデル
	Object* m_subModels[8];
	//ターゲット
	Target* m_target;
	//ターゲットマーク
	TargetMark* m_targetMark;
	//状態
	State m_state;
	//移動量
	float m_movePar;
	//Tween
	Tween* m_tween;
public:
	//コンストラクタ
	TargetBox(Scene* scene);
	//デストラクタ
	~TargetBox()override = default;
	//アップデート
	void ObjectUpdate(float deltatime);
private:
	//開く
	void Open();
	//とじる
	void Close();
	//開閉処理
	void Move();
};