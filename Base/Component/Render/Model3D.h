// ================================================================ 
// ファイル名 : Model3D.h
// 作成者 : 景山碧天
// 説明 :  モデル描画を行う
// ================================================================

#pragma once
#include"Base/Component/Component.h"
#include"Base/Config.h"

class Camera;

class Model3D :public Component
{
private:
	//描画オーダー
	int m_renderOrder;
	//モデル
	DirectX::Model* m_model;
	//ポジション
	DirectX::SimpleMath::Vector3 m_position;
	//サイズ
	DirectX::SimpleMath::Vector3 m_scale;
	//回転
	DirectX::SimpleMath::Quaternion m_rotate;
	//matrix
	DirectX::SimpleMath::Matrix m_matrix;
	//個別設定描画
	std::function<void(const Camera&)> m_render;
	//先送り描画フラグ
	bool m_isAfterRender;
	//影生成フラグ
	bool m_isShadow;
public:
	//コンストラクタ
	Model3D(Object* object, std::string modelname = Config::NONE_FILE, int renderOrder = 0);
	//デストラクタ
	~Model3D();
	//モデルロード
	void Load(std::string filename);
	//matrix取得
	DirectX::SimpleMath::Matrix GetWorldMatrix();
	//描画
	void Render(const Camera& camera);
	//描画順変更
	void ChangeRenderOrder(int renderOrder);

	//レンダーオーダーゲット
	int GetRenderOrder()const { return m_renderOrder; }
	//モデル取得
	DirectX::Model* GetModel() { return m_model; }
	//ポジションセット
	void SetPosition(DirectX::SimpleMath::Vector3 position);
	//サイズセット
	void SetScale(DirectX::SimpleMath::Vector3 scale);
	//スケールセット
	void SetRotate(DirectX::SimpleMath::Quaternion roteto);
	DirectX::SimpleMath::Quaternion GetRotate()const { return m_rotate; }
	//matrix取得
	DirectX::SimpleMath::Matrix GetMatrix() const { return m_matrix; }
	//個別描画セット
	void SetRender(std::function<void(const Camera&)> render);
	//先送り描画フラグセット
	void SetIsAfterDraw(bool isafterDraw) { m_isAfterRender = isafterDraw; }
	//先送り描画フラグ取得
	bool GetIsAfterDraw()const { return m_isAfterRender; }
	//影生成フラグセット
	void SetIsShadow(bool isshadow) { m_isShadow = isshadow; }
	//影生成フラグ取得
	bool GetIsShadow()const { return m_isShadow; }
	//シーン切り替えイベント
	void LoadScene(Scene* scene);
};

