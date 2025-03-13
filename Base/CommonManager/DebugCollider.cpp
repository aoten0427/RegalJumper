// ================================================================ 
// ファイル名 : DebugCollider.cpp
// 作成者 : 景山碧天
// 説明 :  コライダーデバッグ表示
// ================================================================

#include"pch.h"
#include"DebugCollider.h"
#include"DeviceResources.h"
#include "Libraries/Microsoft/DebugDraw.h"
#include"Base/Object/Object.h"
#include"Base/Camera/Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="device">デバイス</param>
/// <param name="context">コンテクスト</param>
DebugCollider::DebugCollider(ID3D11Device* device, ID3D11DeviceContext* context)
	:
	m_primitiveBatch{nullptr},
	m_basicEffect{nullptr},
	m_inputLayout{nullptr},
	m_aabb{}
{
	using namespace DirectX;

	//プリミティブバッチ作成
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);

	// ベーシックエフェクトを作成する
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetVertexColorEnabled(true);
	m_basicEffect->SetLightingEnabled(false);
	m_basicEffect->SetTextureEnabled(false);

	// 入力レイアウトを作成する
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionColor>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="context">コンテクスト</param>
/// <param name="commonStates">コモンステート</param>
/// <param name="camera">カメラ</param>
/// <param name="color">描画色</param>
void DebugCollider::Render(ID3D11DeviceContext* context, DirectX::CommonStates* commonStates, const Camera& camera, const DirectX::XMVECTOR& color)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	context->OMSetBlendState(commonStates->Opaque(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(commonStates->DepthDefault(), 0);
	context->RSSetState(commonStates->CullClockwise());


	// 変換行列を設定する
	Matrix world{ Matrix::Identity };
	m_basicEffect->SetWorld(world);
	m_basicEffect->SetView(camera.GetViewMatrix());
	m_basicEffect->SetProjection(camera.GetProjectionMatrix());
	m_basicEffect->Apply(context);

	context->IASetInputLayout(m_inputLayout.Get());

	m_primitiveBatch->Begin();

	//AABB描画
	for (auto& aabb : m_aabb)
	{
		DirectX::BoundingOrientedBox box;
		box.Extents = Vector3(0.5f, 0.5f, 0.5f);
		box.Transform(box, aabb->GetWorldMatrix());
		DX::Draw(m_primitiveBatch.get(), box);
	}

	//OBB描画
	for (auto& obb : m_obb)
	{
		DirectX::BoundingOrientedBox box;
		box.Extents = Vector3(0.5f, 0.5f, 0.5f);
		box.Transform(box, obb->GetWorldMatrix());
		DX::Draw(m_primitiveBatch.get(), box);
	}

	//球描画
	for (auto& sphere : m_sphere)
	{
		DirectX::BoundingSphere Bsphere;
		Bsphere.Transform(Bsphere, sphere->GetWorldMatrix());
		Bsphere.Radius = sphere->GetRadius();
		DX::Draw(m_primitiveBatch.get(), Bsphere, color);
	}

	//線分描画
	for (auto& segment : m_segment)
	{
		m_primitiveBatch->DrawLine(VertexPositionColor(segment->GetWorldStartPos(), color),
			VertexPositionColor(segment->GetWorldEndPos(), color));
	}

	m_primitiveBatch->End();
}

/// <summary>
/// コライダー追加
/// </summary>
/// <param name="collider">追加コライダー</param>
void DebugCollider::AddCollider(Collider* collider)
{
	switch (collider->GetColliderTag())
	{
	case Collider::ColliderTag::AABB:
		m_aabb.insert(static_cast<AABB*>(collider));
		break;
	case Collider::ColliderTag::OBB:
		m_obb.insert(static_cast<OBB*>(collider));
		break;
	case Collider::ColliderTag::SPHERE:
		m_sphere.insert(static_cast<Sphere*>(collider));
		break;
	case Collider::ColliderTag::SEGMENT:
		m_segment.insert(static_cast<Segment*>(collider));
		break;
	case Collider::ColliderTag::TRIANGLE:
		break;
	case Collider::ColliderTag::QUAD:
		break;
	default:
		break;
	}
}

/// <summary>
/// コライダー削除
/// </summary>
/// <param name="collider">削除コライダー</param>
void DebugCollider::RemoveCollider(Collider* collider)
{
	switch (collider->GetColliderTag())
	{
	case Collider::ColliderTag::AABB:
		m_aabb.erase(static_cast<AABB*>(collider));
		break;
	case Collider::ColliderTag::OBB:
		m_obb.erase(static_cast<OBB*>(collider));
		break;
	case Collider::ColliderTag::SPHERE:
		m_sphere.erase(static_cast<Sphere*>(collider));
		break;
	case Collider::ColliderTag::SEGMENT:
		m_segment.erase(static_cast<Segment*>(collider));
		break;
	case Collider::ColliderTag::TRIANGLE:
		break;
	case Collider::ColliderTag::QUAD:
		break;
	default:
		break;
	}
}
