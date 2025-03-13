// ================================================================ 
// �t�@�C���� : Skydome.h
// �쐬�� : �i�R�ɓV
// ���� :  �V��
// ================================================================

#include"pch.h"
#include"Skydome.h"
#include"Base/Component/Render/Model3D.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�����V�[��</param>
Skydome::Skydome(Scene* scene):Object(scene)
{
	Model3D* model = AddComponent<Model3D>(this, "Skydome");
	using namespace DirectX;
	model->GetModel()->UpdateEffects([](DirectX::IEffect* effect)
		{
			// �x�[�V�b�N�G�t�F�N�g��ݒ肷��
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				//���C�g������
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);


				// ���f����������������
				basicEffect->SetEmissiveColor(XMVECTOR{ 0.5f,0.5f,0.5f,1 });
			}
		}
	);
	model->SetScale(SimpleMath::Vector3(30.0f, 30.0f, 30.0f));
	model->SetPosition(SimpleMath::Vector3(0, 0, -1000));
	model->SetIsShadow(false);

}
