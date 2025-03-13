// ================================================================ 
// ファイル名 : PrimitiveRenderer.h
// 作成者 : 景山碧天
// 説明 :  プリミティブバッチでの描画を行う
// ================================================================

#pragma once
#include"Base/Component/Component.h"
#include"Base/Config.h"

class Camera;

class PrimitiveRenderer :public Component
{
public:
	//UI判定取得
	bool GetisUiRender()const { return m_isUi; }
	//描画オーダー取得
	const int& GetRenderOrder() const { return m_renderOrder; }
	//画像取得
	ID3D11ShaderResourceView* GetImage() { return m_texture.Get(); }
	//個別描画セット
	void SetRender(std::function<void(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)> render) { m_render = render; }
private:
	//UI判定
	bool m_isUi;
	//描画オーダー
	int m_renderOrder;
	//画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	//個別描画
	std::function<void(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)> m_render;
public:
	//コンストラクタ
	PrimitiveRenderer(Object* object,std::string filename = Config::NONE_FILE ,int renderOrder = 0, bool ui = false);
	//デストラクタ
	~PrimitiveRenderer();

	//描画
	virtual void Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera);
	//画像ロード
	void Load(std::string filename);
	//描画オーダーセット
	void SetRenderOrder(int order);
	//シーン切り替えイベント
	void LoadScene(Scene* scene);
};
