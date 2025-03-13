// ================================================================ 
// ファイル名 : SpiderModelEnter.h
// 作成者 : 景山碧天
// 説明 :  蜘蛛が出現するときの描画状態
// ================================================================
#pragma once
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelState.h"
#include"Base/Resource/ShaderManager.h"
#include"Base/Scene/Scene.h"

class CommonResources;
template<typename...Args>
class Observer;
class Tween;
class Sound;

class SpiderModelEnter :public SpiderModelState
{
private:
	struct TCBuff
	{
		DirectX::SimpleMath::Vector4 Time;
	};
private:
	//コモンリソース
	CommonResources* m_resources;
	//スパイダーモデル
	SpiderModels* m_spiderModel;
	//シェーダー関係
	ShaderSet m_shaderSet;
	//モザイクテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_mosaicTexture;
	//タイマー用定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_tcBuff;
	//ブレンドステート
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;
	//変化用タイマー
	float m_timer;
	//変化再生、停止オブザーバー
	Observer<Scene::State>* m_playbackObserver;
	//変化用Tween
	Tween* m_tween;
	//ワープサウンド
	Sound* m_warpSound;
public:
	//コンストラクタ
	SpiderModelEnter(SpiderModelStateMachine* machine, SpiderModels* spidermodel);
	//デストラクタ
	~SpiderModelEnter()override = default;
	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
	//描画処理
	void Render(const Camera& camera)override;
private:
	void CheckPlayBack(Scene::State state);
};