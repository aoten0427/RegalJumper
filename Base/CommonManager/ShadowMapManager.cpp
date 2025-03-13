#include"pch.h"
#include"ShadowMapManager.h"
#include"Base/CommonResources.h"
#include"DeviceResources.h"
#include"Libraries/Microsoft/RenderTexture.h"
#include"Base/Resource/DepthResources.h"
#include"Base/Component/Render/Model3D.h"

constexpr int SHADOWMAP_SIZE = 4096;

ShadowMapManager::ShadowMapManager(CommonResources* commonResources)
	:
	m_commonResources{commonResources},
	m_shadowMapRT{nullptr},
	m_depthResources{nullptr},
	m_data{}
{
	//auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	//m_shadowMapRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
	//m_shadowMapRT->SetDevice(device);
	//m_shadowMapRT->SetWindow(RECT{ 0,0,SHADOWMAP_SIZE,SHADOWMAP_SIZE });

	//m_depthResources = std::make_unique<DepthResources>(device,SHADOWMAP_SIZE);

	//m_shadowMapShader.vertexShader = ShaderManager::CreateVSShader(device, "ShadowMapVS.cso");
	//m_shadowMapShader.pixelShader = ShaderManager::CreatePSShader(device, "ShadowMapPS.cso");
	//m_shadowMapShader.cBuffer = ShaderManager::CreateConstantBuffer<cbLight>(device);

	//// シャドウマップ用のサンプラーを作成する
	//D3D11_SAMPLER_DESC samplerDesc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
	//samplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	//samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	//samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	//samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	//samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS;
	//DX::ThrowIfFailed(
	//	device->CreateSamplerState(&samplerDesc, m_shadowMapSampler.ReleaseAndGetAddressOf())
	//);

	//m_data.m_sampler = m_shadowMapSampler.Get();
}

ShadowMapManager::~ShadowMapManager()
{

}

ShadowMapData* ShadowMapManager::GetShadowMapData()
{
	return &m_data;
}



void ShadowMapManager::Render(std::vector<Model3D*>& models, const Camera& camera)
{
	UNREFERENCED_PARAMETER(camera);
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	auto rtv = m_shadowMapRT->GetRenderTargetView();
	auto srv = m_shadowMapRT->GetShaderResourceView();
	auto dsv = m_depthResources->GetDepthStencilView();
	//レンダーターゲットを切り変える
	context->ClearRenderTargetView(rtv, DirectX::Colors::White);
	context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	context->OMSetRenderTargets(1, &rtv, dsv);
	const D3D11_VIEWPORT vp = { 0,0,SHADOWMAP_SIZE,SHADOWMAP_SIZE ,0,1 };
	context->RSSetViewports(1, &vp);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	int t = 50;
	/*Vector3 lightPosition = Vector3(10, 10, 0);
	Vector3 lightDir = Vector3(-1, -1, 0);*/
	Vector3 lightPosition = Vector3(0, 400, -1000);
	Vector3 lightDir = Vector3(0, -1,0);
	lightDir.Normalize();
	//ライト
	const Matrix lightView = Matrix::CreateLookAt(
		lightPosition,
		lightPosition + lightDir,
		Vector3::UnitY
	);

	const Matrix lightProjection = Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(90),
		1.0f,
		0.1f,
		2000.0f
	);
	const Matrix viewProj = lightView * lightProjection;
	cbLight cbuff;
	cbuff.lightViewProjection = viewProj.Transpose();
	cbuff.lightPosition = lightPosition;
	cbuff.lightDirection = lightDir;
	cbuff.lightAmbient = Color(0.2f, 0.2f, 0.2f);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_shadowMapShader.cBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_shadowMapShader.cBuffer.Get() };
	
	for (auto& model : models)
	{
		if (!model->GetIsShadow())continue;
		if (model->GetModel() == nullptr)continue;
		model->GetModel()->Draw(context, *states, model->GetWorldMatrix(), lightView, lightProjection, false, [&]() {

			context->VSSetConstantBuffers(1, 1, cb);
			context->PSSetConstantBuffers(1, 1, cb);

			/*context->IASetInputLayout(m_shadowMapShader.inputLayout.Get());*/
			context->VSSetShader(m_shadowMapShader.vertexShader.Get(),nullptr,0);
			context->PSSetShader(m_shadowMapShader.pixelShader.Get(), nullptr, 0);
			});
	}


	m_data.m_shaderResourcesView = m_shadowMapRT->GetShaderResourceView();
	m_data.m_cbuff = m_shadowMapShader.cBuffer.Get();
	

	//レンダーターゲットを戻す
	auto defaultRTV = m_commonResources->GetDeviceResources()->GetRenderTargetView();
	auto defaultDSV = m_commonResources->GetDeviceResources()->GetDepthStencilView();

	context->OMSetRenderTargets(1, &defaultRTV, defaultDSV);

	const auto& defaultVP = m_commonResources->GetDeviceResources()->GetScreenViewport();
	context->RSSetViewports(1, &defaultVP);

	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	context->PSSetShaderResources(1, 1, nullsrv);
}
