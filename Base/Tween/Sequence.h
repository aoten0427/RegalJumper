// ================================================================ 
// ファイル名 : Sequence.h
// 作成者 : 景山碧天
// 説明 :  Tweenを複数管理する
// ================================================================
#pragma once
#include"Base/Component/Component.h"

class TweenCore;

class Sequence :public Component
{

private:
	//コア
	std::vector<TweenCore*> m_cores;
	//現在動かしているコア番号
	int m_activeNumber;
public:
	Sequence(Object* object);
	~Sequence();
	//Int追加
	TweenCore& AppendInt(int& origin, int end, float time);
	//float追加
	TweenCore& AppendFloat(float& origin, float end, float time);
	//Vector2追加
	TweenCore& AppendVector2(DirectX::SimpleMath::Vector2& origin, DirectX::SimpleMath::Vector2 end, float time);
	//Vector3追加
	TweenCore& AppendVector3(DirectX::SimpleMath::Vector3& origin, DirectX::SimpleMath::Vector3 end, float time);
	//Vector4追加
	TweenCore& AppendVector4(DirectX::SimpleMath::Vector4& origin, DirectX::SimpleMath::Vector4 end, float time);
	//Quaternion追加
	TweenCore& AppendQuaternion(DirectX::SimpleMath::Quaternion& origin, DirectX::SimpleMath::Quaternion end, float time);
	
	//完了
	void Kill();
	//再開
	void Play();
	//一時停止
	void Pause();
	//ループ
	void Loop();
	//リスタート
	void ReStart();
private:
	//追加時のプロセス
	void AppendProcess(TweenCore* newCore);
	
};