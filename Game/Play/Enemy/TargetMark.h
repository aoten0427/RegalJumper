// ================================================================ 
// ファイル名 : TargetMark.h
// 作成者 : 景山碧天
// 説明 :  ターゲット表示マーク
// ================================================================
#pragma once
#include"Base/Object/Object.h"

class Camera;
class PrimitiveRenderer;
class Tween;

class TargetMark :public Object
{
private:
	//描画データ
	PrimitiveRenderer* m_renderer;
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//大きさ
	float m_size;
	//変化用Tween
	Tween* m_tween;
public:
	//コンストラクタ
	TargetMark(Scene* scene, Object* holder);
	//デストラクタ
	~TargetMark()override = default;
	//描画
	void Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera);
	//開く
	void Open();
	//閉じる
	void Close();
};