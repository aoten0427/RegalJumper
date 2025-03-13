// ================================================================ 
// ファイル名 : UserInterface.h
// 作成者 : 景山碧天
// 説明 :  UIクラス
// ================================================================

#pragma once
#include"Base/Object/Object.h"
#include"Base/Config.h"

class Canvas;
class Camera;
class PrimitiveRenderer;

class UserInterface:public Object
{
public:
	//データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4    Position;
		DirectX::SimpleMath::Vector2	WindowSize;
		DirectX::SimpleMath::Vector2	Size;
		DirectX::SimpleMath::Vector4    Color;
		DirectX::SimpleMath::Vector2    Extent;
		DirectX::SimpleMath::Vector2    Offset;
		DirectX::SimpleMath::Vector4    ClipRange;
		DirectX::SimpleMath::Vector4    Free;
	};
public:
	//ゲッター
	Canvas* GetCanvas() const { return m_canvas; }

	Microsoft::WRL::ComPtr<ID3D11Buffer> GetCBuffer() { return m_CBuffer; }
	Microsoft::WRL::ComPtr<ID3D11InputLayout> GetInputLayout() { return m_inputLayout; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture() { return m_texture; }
	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetVertexShader() { return m_vertexShader; }
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetPixelShader() { return m_pixelShader; }
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> GetGeometryShader() { return m_geometryShader; }

	DirectX::SimpleMath::Vector2 GetPosition()const { return m_position; }
	DirectX::SimpleMath::Vector2 GetSize()const { return m_size; }
	DirectX::SimpleMath::Vector4 GetColor()const { return m_color; }
	DirectX::SimpleMath::Vector2 GetExtent()const { return m_extent; }
	DirectX::SimpleMath::Vector2 GetOffset()const { return m_offset; }
	DirectX::SimpleMath::Vector4 GetClipRange()const { return m_clipRange; }
	bool GetMouseEventFlag()const { return m_mouseEventFlag; }
	//セッター
	void SetPosition(const DirectX::SimpleMath::Vector2 position) { m_position = position; }
	void SetSize(const DirectX::SimpleMath::Vector2 size) { m_size = size; }
	void SetColor(const DirectX::SimpleMath::Vector4 color) { m_color = color; }
	void SetExtent(const DirectX::SimpleMath::Vector2 extent) { m_extent = extent; }
	void SetOffset(const DirectX::SimpleMath::Vector2 offset) { m_offset = offset; }
	void SetClipRange(const DirectX::SimpleMath::Vector4 range) { m_clipRange = range; }
	void SetMouseEventFlag(bool mouseEventflag) { m_mouseEventFlag = mouseEventflag; }
	void SetFreeElement(const DirectX::SimpleMath::Vector4 free) { m_freeElement = free; }
private:
	//キャンバス
	Canvas* m_canvas;
	//描画
	PrimitiveRenderer* m_render;
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//ポジション
	DirectX::SimpleMath::Vector2 m_position;
	//サイズ
	DirectX::SimpleMath::Vector2 m_size;
	//色
	DirectX::SimpleMath::Vector4 m_color;
	//幅
	DirectX::SimpleMath::Vector2 m_extent;
	//オフセット
	DirectX::SimpleMath::Vector2 m_offset;
	//切り取り範囲
	DirectX::SimpleMath::Vector4 m_clipRange;
	//フリー
	DirectX::SimpleMath::Vector4 m_freeElement;
	//マウスによるイベントを実行するか判断
	bool m_mouseEventFlag;
public:
	UserInterface(Canvas* canvas,std::string filename = "Quad", int renderorder = 0);
	virtual ~UserInterface() override;
	//描画
	void Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera);
	//描画準設定
	void SetRenderOrder(int order);
	//テクスチャセット
	void SetTexture(std::string filename);
	//バーテックスシェーダー設定
	void SetVertexShader(std::string filename);
	//ピクセルシェーダ設定
	void SetPixelShader(std::string filename);
	//描画
	void SetRender(std::function<void(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)> render);
	//シーン切り替え時イベント
	virtual void LoadScene(Scene* scene) override;

	//マウス感知イベント
	virtual void MouseWithinEvent(bool within) { UNREFERENCED_PARAMETER(within); };
	//左クリックイベント
	virtual void LeftClickEvent(bool within) { UNREFERENCED_PARAMETER(within); };
};