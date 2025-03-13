// ================================================================ 
// ファイル名 : RenderManager.h
// 作成者 : 景山碧天
// 説明 :  描画を行う
// ================================================================

#pragma once
#include"Base/CommonManager/ShadowMapManager.h"
#include"Base/CommonManager/ShadowMapManager.h"

class CommonResources;
class Camera;
class Model3D;
class PrimitiveRenderer;


class RenderManager
{
private:
	CommonResources* m_commonResources;
	//プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;
	//3Dモデル
	std::vector<Model3D*>  m_model3Ds;
	//レンダラー
	std::vector<PrimitiveRenderer*> m_primitiveRenderer;
	//シャドウマップ
	std::unique_ptr<ShadowMapManager> m_shadowMap;
public:
	//コンストラクタ
	RenderManager(CommonResources* commonResources);
	//デストラクタ
	~RenderManager() = default;

	//3Dモデルの追加と削除
	void AddModel3D(Model3D* model3D);
	void RemoveModel3D(Model3D* model3D);
	//描画順変更
	void ChangeRenderOrder(Model3D* model3D);

	//レンダラー追加と削除
	void AddPrimitiveRenderer(PrimitiveRenderer* render);
	void RemovePrimitiveRenderer(PrimitiveRenderer* render);
	//描画順変更
	void ChangeRenderOrder(PrimitiveRenderer* render);

	//描画
	void Render(const Camera& camera);

	ShadowMapData* GetShadowData() { return m_shadowMap->GetShadowMapData(); }
};