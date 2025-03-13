// ================================================================ 
// ファイル名 : DebugCollider.h
// 作成者 : 景山碧天
// 説明 :  コライダーデバッグ表示
// ================================================================

#pragma once
#include"Base/Component/Collider/Collider.h"

class Camera;

class DebugCollider
{
private:
	//プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
	//ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	//インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//各コライダー
	std::unordered_set<AABB*> m_aabb;
	std::unordered_set<OBB*>  m_obb;
	std::unordered_set<Sphere*> m_sphere;
	std::unordered_set<Segment*> m_segment;
public:
	//コンストラクタ
	DebugCollider(ID3D11Device* device, ID3D11DeviceContext* context);
	//デストラクタ
	~DebugCollider() = default;
	//レンダー
	void Render(ID3D11DeviceContext* context,
		DirectX::CommonStates* commonStates,
		const Camera& camera,
		const DirectX::XMVECTOR& color = DirectX::Colors::White);
	//コライダー追加
	void AddCollider(Collider* collider);
	//コライダー削除
	void RemoveCollider(Collider* collider);
};