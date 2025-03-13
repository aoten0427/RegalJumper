// ================================================================ 
// ファイル名 : SpiderModelNormal.h
// 作成者 : 景山碧天
// 説明 :  Select画面での蜘蛛の描画状態
// ================================================================
#pragma once
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelState.h"
#include"Base/Resource/ShaderManager.h"

class CommonResources;

class SpiderModelNormal :public SpiderModelState
{
private:
	//コモンリソース
	CommonResources* m_resources;
	//スパイダーモデル
	SpiderModels* m_spiderModel;
	//シェーダー関係
	ShaderSet m_shaderSet;
public:
	//コンストラクタ
	SpiderModelNormal(SpiderModelStateMachine* machine, SpiderModels* spidermodel);
	//デストラクタ
	~SpiderModelNormal()override = default;
	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
	//描画処理
	void Render(const Camera& camera)override;
};