// ================================================================ 
// ファイル名 : SpiderModelExit.h
// 作成者 : 景山碧天
// 説明 :  蜘蛛が消失するときの描画状態
// ================================================================
#pragma once
#include"Game/Play/Player/SpiderModel/SpiderModelState/SpiderModelState.h"
#include"Base/Resource/ShaderManager.h"

class CommonResources;
template<typename...Args>
class Subject;
class Tween;
class Sound;

class SpiderModelExit :public SpiderModelState
{
public:
	struct CBuff
	{
		DirectX::SimpleMath::Vector2 Time;
		DirectX::SimpleMath::Vector2 CenterHeight;
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
	//終了通知
	Subject<>* m_finishSubject;
	//変化用Tween
	Tween* m_tween;
	//ワープサウンド
	Sound* m_warpSound;
public:
	//コンストラクタ
	SpiderModelExit(SpiderModelStateMachine* machine, SpiderModels* spidermodel);
	//デストラクタ
	~SpiderModelExit()override = default;
	// 事前更新する
	void PreUpdate()override;
	// 更新する
	void Update(float deltaTime)override;
	// 事後更新する
	void PostUpdate()override;
	//描画処理
	void Render(const Camera& camera)override;
};