// ================================================================ 
// ファイル名 : SpiderModelPlay.h
// 作成者 : 景山碧天
// 説明 :  Play画面での蜘蛛の描画状態
// ================================================================
#pragma once
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelState.h"
#include"Base/Resource/ShaderManager.h"

class CommonResources;

class SpiderModelPlay :public SpiderModelState
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
	SpiderModelPlay(SpiderModelStateMachine* machine, SpiderModels* spidermodel);
	//デストラクタ
	~SpiderModelPlay()override = default;
	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
	//描画処理
	void Render(const Camera& camera)override;
};