// ================================================================ 
// ファイル名 : ThreadModel.h
// 作成者 : 景山碧天
// 説明 :  糸のモデル
// ================================================================

#pragma once
#include"Base/Object/Object.h"

class Thread;
class Model3D;
class Camera;

class ThreadModel :public Object
{
private:
	//糸
	Thread* m_thread;
	//モデル
	Model3D* m_model;
	//
	std::vector<float> m_knot;
public:
	//コンストラクタ
	ThreadModel(Scene* scene, Thread* thread);
	//デストラクタ
	~ThreadModel()override = default;
	//描画
	void Render(const Camera& camera);

private:
	//ノットベクトルを計算
	std::vector<float> ClampedKnotVector(int p, int n);
	//Bスプラインの基底関数を計算
	float BasisFunction(const std::vector<float>& u, int j, int k, float t);
	// Bスプライン曲線を計算
	std::vector<DirectX::SimpleMath::Vector3> ComputeBSplineCurve(const std::vector<DirectX::SimpleMath::Vector3>& P, int n, float step = 0.01f);
};