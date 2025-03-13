#pragma once

class DepthResources
{
public:
	ID3D11Texture2D* GetTexture2D()const { return m_depthStencilTexture.Get(); }
	ID3D11DepthStencilView* GetDepthStencilView()const { return m_depthStencilView.Get(); }
private:
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthStencilTexture;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
public:
	DepthResources(ID3D11Device* device, UINT resolution = 512);
	~DepthResources();
};