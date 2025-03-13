// ================================================================ 
// ファイル名 : Tween.h
// 作成者 : 景山碧天
// 説明 :  Tweenを扱うためのクラス
// ================================================================

#pragma once
#include"Base/Component/Component.h"

class TweenCore;

class Tween :public Component
{
private:
	//Tween本体
	TweenCore* m_core;
	//再利用フラグ
	bool m_reuse;
public:
	//コンストラクタ
	Tween(Object* object,bool reuse = false);
	//デストラクタ
	~Tween();
	//アップデート
	void Update(float deltatime)override;
	//Int制御
	TweenCore& DoInt(int& origin, int end, float time);
	//float制御
	TweenCore& DoFloat(float& origin, float end, float time);
	//Vector2制御
	TweenCore& DoVector2(DirectX::SimpleMath::Vector2& origin, DirectX::SimpleMath::Vector2 end, float time);
	//Vector3制御
	TweenCore& DoVector3(DirectX::SimpleMath::Vector3& origin, DirectX::SimpleMath::Vector3 end, float time);
	//Vector4制御
	TweenCore& DoVector4(DirectX::SimpleMath::Vector4& origin, DirectX::SimpleMath::Vector4 end, float time);
	//Quaternion制御
	TweenCore& DOQuaternion(DirectX::SimpleMath::Quaternion& origin, DirectX::SimpleMath::Quaternion end, float time);

	//完了
	void Kill();
	//一時停止
	void Pause();
	//再開
	void Play();
};
