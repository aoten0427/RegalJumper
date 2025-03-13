// ================================================================ 
// ファイル名 : UserInterface.cpp
// 作成者 : 景山碧天
// 説明 :  UIクラス
// ================================================================

#include"pch.h"
#include"UserInterface.h"
#include"Base/CommonResources.h"
#include"DeviceResources.h"
#include"Base/Resource/ShaderManager.h"
#include"Base/Resource/GameResources.h"
#include"Base/Scene/Scene.h"
#include"Base/CommonManager/UIManager.h"
#include"Base/Canvas/Canvas.h"
#include"Base/Screen.h"
#include"Base/Component/Render/PrimitiveRenderer.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">キャンバス</param>
/// <param name="filename">読み込み画像</param>
/// <param name="renderorder">優先度</param>
UserInterface::UserInterface(Canvas* canvas, std::string filename, int renderorder) :Object(canvas->GetScene())
	,
	m_canvas{canvas},
	m_render{ nullptr },
	m_CBuffer{},
	m_inputLayout{ nullptr },
	m_vertexShader{ nullptr },
	m_pixelShader{ nullptr },
	m_geometryShader{ nullptr },
	m_position{ DirectX::SimpleMath::Vector2(Screen::CENTER_X,Screen::CENTER_Y) },
	m_size{ DirectX::SimpleMath::Vector2(100,100) },
	m_color{ DirectX::SimpleMath::Vector4(1.0f,1.0f,1.0f,1.0f) },
	m_extent{ DirectX::SimpleMath::Vector2(1.0f,1.0f) },
	m_offset{ DirectX::SimpleMath::Vector2(0.5f,0.5f) },
	m_clipRange{ DirectX::SimpleMath::Vector4(0.0f,0.0f,1.0f,1.0f) },
	m_freeElement{DirectX::SimpleMath::Vector4::Zero},
	m_mouseEventFlag{ false }
{
	//マネージャーへ登録
	GetScene()->GetUIManager()->AddUserInterface(this);

	//レンダラー作成
	m_render = AddComponent<PrimitiveRenderer>(this, filename, renderorder,true);
	m_render->SetRender(std::bind(&UserInterface::Render, this, std::placeholders::_1, std::placeholders::_2));

	//シェーダー設定
	auto device = GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	m_inputLayout = ShaderManager::CreateInputLayout(device,NOMAL_INPUT_LAYOUT , "UIVS.cso");
	m_vertexShader = ShaderManager::CreateVSShader(device, "UIVS.cso");
	m_geometryShader = ShaderManager::CreateGSShader(device, "UIGS.cso");
	m_pixelShader = ShaderManager::CreatePSShader(device, "UIPS.cso");
	m_CBuffer = ShaderManager::CreateConstantBuffer<ConstBuffer>(device);
	//画像読み込み
	if (filename != Config::NONE_FILE)SetTexture(filename);
}

/// <summary>
/// デストラクタ
/// </summary>
UserInterface::~UserInterface()
{
	//マネージャーから削除
	GetScene()->GetUIManager()->ReMoveUserInterface(this);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="primitiveBatch">プリミティブバッチ</param>
/// <param name="camera">カメラ</param>
void UserInterface::Render(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)
{
	UNREFERENCED_PARAMETER(camera);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	auto context = GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto state = GetCommonResources()->GetCommonStates();

	VertexPositionTexture vertex{};

	//設定の登録
	ConstBuffer cbuff;
	cbuff.WindowSize = Vector2(Screen::WIDTH, Screen::HEIGHT);
	cbuff.Position = Vector4(m_position.x, m_position.y, 0, 0);
	cbuff.Size = m_size;
	cbuff.Color = m_color;
	cbuff.Extent = m_extent;
	cbuff.Offset = m_offset;
	cbuff.ClipRange = m_clipRange;
	cbuff.Free = m_freeElement;
	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { state->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	//	半透明描画指定
	ID3D11BlendState* blendstate = state->NonPremultiplied();

	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(state->DepthNone(), 0);

	context->RSSetState(state->CullNone());

	//	シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());


	//	インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//描画
	primitiveBatch->Begin();
	primitiveBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex, 1);
	primitiveBatch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

/// <summary>
/// 描画順変更
/// </summary>
/// <param name="order">優先度</param>
void UserInterface::SetRenderOrder(int order)
{
	m_render->SetRenderOrder(order);
}

/// <summary>
/// 画像読み込み
/// </summary>
/// <param name="filename">読み込み画像名</param>
void UserInterface::SetTexture(std::string filename)
{
	auto resources = GameResources::GetInstance();
	m_texture = resources->GetTexture(filename);
}

/// <summary>
/// 頂点シェーダセット
/// </summary>
/// <param name="filename">VSシェーダー名</param>
void UserInterface::SetVertexShader(std::string filename)
{
	auto device = GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	m_inputLayout = ShaderManager::CreateInputLayout(device, NOMAL_INPUT_LAYOUT, filename);
	m_vertexShader = ShaderManager::CreateVSShader(device, filename);
}

/// <summary>
/// ピクセルシェーダセット
/// </summary>
/// <param name="filename">PSシェーダー名</param>
void UserInterface::SetPixelShader(std::string filename)
{
	auto device = GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	m_pixelShader = ShaderManager::CreatePSShader(device, filename);
}

/// <summary>
/// 個別描画セット
/// </summary>
/// <param name="render">描画を設定</param>
void UserInterface::SetRender(std::function<void(DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>* primitiveBatch, const Camera& camera)> render)
{
	m_render->SetRender(render);
}

/// <summary>
/// シーン切り替えイベント
/// </summary>
/// <param name="scene">変更シーン</param>
void UserInterface::LoadScene(Scene* scene)
{
	UNREFERENCED_PARAMETER(scene);
	scene->GetUIManager()->AddUserInterface(this);
	m_canvas = scene->GetCanvas();
	m_render->LoadScene(scene);
}
