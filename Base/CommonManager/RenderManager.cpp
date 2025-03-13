// ================================================================ 
// ファイル名 : RenderManager.cpp
// 作成者 : 景山碧天
// 説明 :  描画を行う
// ================================================================

#include"pch.h"
#include"RenderManager.h"
#include"Base/CommonResources.h"
#include"DeviceResources.h"
#include"Base/Component/Render/Model3D.h"
#include"Base/Component/Render/PrimitiveRenderer.h"
#include"Base/CommonManager/ShadowMapManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="context">コンテクスト</param>
/// <param name="states">コモンステート</param>
RenderManager::RenderManager(CommonResources* commonResources)
	:
	m_commonResources{commonResources}
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//プリミティブバッチの作成
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(context);

	m_shadowMap = std::make_unique<ShadowMapManager>(commonResources);
}

/// <summary>
/// モデルの追加
/// </summary>
/// <param name="model3D">追加モデル</param>
void RenderManager::AddModel3D(Model3D* model3D)
{
	//オーダーの場所へ追加
	auto itr = m_model3Ds.begin();
	//挿入場所検索
	while (itr != m_model3Ds.end()&& model3D->GetRenderOrder() > (*itr)->GetRenderOrder())
	{
		itr++;
	}
	m_model3Ds.insert(itr, model3D);
}

/// <summary>
/// モデル削除
/// </summary>
/// <param name="model3D">削除モデル</param>
void RenderManager::RemoveModel3D(Model3D* model3D)
{
	auto remove = std::find(m_model3Ds.begin(), m_model3Ds.end(), model3D);
	if (remove != m_model3Ds.end())
	{
		m_model3Ds.erase(remove);
	}
}

/// <summary>
/// 描画順変更(モデル)
/// </summary>
/// <param name="model3D">変更モデル</param>
void RenderManager::ChangeRenderOrder(Model3D* model3D)
{
	//移動要素を検索
	auto move = std::find(m_model3Ds.begin(), m_model3Ds.end(),model3D);
	if (move == m_model3Ds.end())return;

	//一時保存して配列から削除
	auto element = std::move(*move);
	m_model3Ds.erase(move);

	//挿入場所検索
	auto change = m_model3Ds.begin();
	while (change != m_model3Ds.end() && model3D->GetRenderOrder() > (*change)->GetRenderOrder())
	{
		change++;
	}

	//挿入
	m_model3Ds.insert(change, std::move(element));
}

/// <summary>
/// 画像レンダラー追加
/// </summary>
/// <param name="render">追加レンダラー</param>
void RenderManager::AddPrimitiveRenderer(PrimitiveRenderer* render)
{
	auto itr = m_primitiveRenderer.begin();
	while (itr != m_primitiveRenderer.end() && render->GetRenderOrder() > (*itr)->GetRenderOrder())
	{
		itr++;
	}
	m_primitiveRenderer.insert(itr, render);
}

/// <summary>
/// 画像レンダラー削除
/// </summary>
/// <param name="render">削除レンダラー</param>
void RenderManager::RemovePrimitiveRenderer(PrimitiveRenderer* render)
{
	auto remove = std::find(m_primitiveRenderer.begin(), m_primitiveRenderer.end(), render);
	if (remove != m_primitiveRenderer.end())
	{
		m_primitiveRenderer.erase(remove);
	}
}

/// <summary>
/// 描画順変更(レンダラー)
/// </summary>
/// <param name="render">変更レンダラー</param>
void RenderManager::ChangeRenderOrder(PrimitiveRenderer* render)
{
	//移動要素を検索
	auto move = std::find(m_primitiveRenderer.begin(), m_primitiveRenderer.end(), render);
	if (move == m_primitiveRenderer.end())return;

	//一時保存して配列から削除
	auto element = std::move(*move);
	m_primitiveRenderer.erase(move);

	//挿入場所検索
	auto change = m_primitiveRenderer.begin();
	while (change != m_primitiveRenderer.end() && render->GetRenderOrder() > (*change)->GetRenderOrder())
	{
		change++;
	}

	//挿入
	m_primitiveRenderer.insert(change, std::move(element));
}

/// <summary>
/// 描画
/// </summary>
/// <param name="camera">描画カメラ</param>
void RenderManager::Render(const Camera& camera)
{
	//シャドウマップ
	/*m_shadowMap->Render(m_model3Ds, camera);*/


	std::vector<Model3D*> afterdraws;
	//モデル描画
	for (auto& model : m_model3Ds)
	{
		if (!model->GetActive())continue;
		if (model->GetIsAfterDraw())
		{
			//描画を先送りする
			afterdraws.push_back(model);
			continue;
		}

		model->Render(camera);
	}

	std::vector<PrimitiveRenderer*> uis;
	//レンダラー描画
	for (auto& renderer : m_primitiveRenderer)
	{
		if (!renderer->GetActive())continue;
		if (renderer->GetisUiRender())
		{
			//UIは先送りする
			uis.push_back(renderer);
			continue;
		}
		renderer->Render(m_primitiveBatch.get(), camera);
	}

	//先送りモデル描画
	for (auto& model : afterdraws)
	{
		model->Render(camera);
	}

	//UI描画
	for (auto& renderer : uis)
	{
		renderer->Render(m_primitiveBatch.get(), camera);
	}
}
