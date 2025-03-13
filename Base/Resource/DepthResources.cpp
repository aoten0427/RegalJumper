#include"pch.h"
#include"DepthResources.h"

DepthResources::DepthResources(ID3D11Device* device, UINT resolution)
{
	// �e�N�X�`���̍쐬�i�[�x�o�b�t�@�p�j
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = resolution;   // ��
	desc.Height = resolution;  // ����
	desc.MipLevels = 1;       // �~�b�v�}�b�v ���x����
	desc.ArraySize = 1;       // �z��T�C�Y
	desc.Format = DXGI_FORMAT_D16_UNORM;  // �t�H�[�}�b�g
	desc.SampleDesc.Count = 1;  // �}���`�T���v�����O�̐ݒ�
	desc.SampleDesc.Quality = 0;  // �}���`�T���v�����O�̕i��
	desc.Usage = D3D11_USAGE_DEFAULT;      // �f�t�H���g�g�p�@
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // �[�x�o�b�t�@�Ƃ��Ďg�p
	desc.CPUAccessFlags = 0;   // CPU����̓A�N�Z�X���Ȃ�
	desc.MiscFlags = 0;   // ���̑��̐ݒ�Ȃ�
	DX::ThrowIfFailed(device->CreateTexture2D(&desc, nullptr,m_depthStencilTexture.GetAddressOf()));

	// �[�x/�X�e���V�� �r���[�̍쐬
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
