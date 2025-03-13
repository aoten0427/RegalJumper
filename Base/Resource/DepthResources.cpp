#include"pch.h"
#include"DepthResources.h"

DepthResources::DepthResources(ID3D11Device* device, UINT resolution)
{
	// テクスチャの作成（深度バッファ用）
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = resolution;   // 幅
	desc.Height = resolution;  // 高さ
	desc.MipLevels = 1;       // ミップマップ レベル数
	desc.ArraySize = 1;       // 配列サイズ
	desc.Format = DXGI_FORMAT_D16_UNORM;  // フォーマット
	desc.SampleDesc.Count = 1;  // マルチサンプリングの設定
	desc.SampleDesc.Quality = 0;  // マルチサンプリングの品質
	desc.Usage = D3D11_USAGE_DEFAULT;      // デフォルト使用法
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // 深度バッファとして使用
	desc.CPUAccessFlags = 0;   // CPUからはアクセスしない
	desc.MiscFlags = 0;   // その他の設定なし
	DX::ThrowIfFailed(device->CreateTexture2D(&desc, nullptr,m_depthStencilTexture.GetAddressOf()));

	// 深度/ステンシル ビューの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Format = DXGI_FORMAT_D16_UNORM;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Flags = 0;
	dsvDesc.Texture2D.MipSlice = 0;
	DX::ThrowIfFailed(device->CreateDepthStencilView(m_depthStencilTexture.Get(), &dsvDesc, m_depthStencilView.GetAddressOf()));
}

DepthResources::~DepthResources()
{
}
