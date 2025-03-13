// ================================================================ 
// �t�@�C���� : Model3D.h
// �쐬�� : �i�R�ɓV
// ���� :  ���f���`����s��
// ================================================================

#pragma once
#include"Base/Component/Component.h"
#include"Base/Config.h"

class Camera;

class Model3D :public Component
{
private:
	//�`��I�[�_�[
	int m_renderOrder;
	//���f��
	DirectX::Model* m_model;
	//�|�W�V����
	DirectX::SimpleMath::Vector3 m_position;
	//�T�C�Y
	DirectX::SimpleMath::Vector3 m_scale;
	//��]
	DirectX::SimpleMath::Quaternion m_rotate;
	//matrix
	DirectX::SimpleMath::Matrix m_matrix;
	//�ʐݒ�`��
	std::function<void(const Camera&)> m_render;
	//�摗��`��t���O
	bool m_isAfterRender;
	//�e�����t���O
	bool m_isShadow;
public:
	//�R���X�g���N�^
	Model3D(Object* object, std::string modelname = Config::NONE_FILE, int renderOrder = 0);
	//�f�X�g���N�^
	~Model3D();
	//���f�����[�h
	void Load(std::string filename);
	//matrix�擾
	DirectX::SimpleMath::Matrix GetWorldMatrix();
	//�`��
	void Render(const Camera& camera);
	//�`�揇�ύX
	void ChangeRenderOrder(int renderOrder);

	//�����_�[�I�[�_�[�Q�b�g
	int GetRenderOrder()const { return m_renderOrder; }
	//���f���擾
	DirectX::Model* GetModel() { return m_model; }
	//�|�W�V�����Z�b�g
	void SetPosition(DirectX::SimpleMath::Vector3 position);
	//�T�C�Y�Z�b�g
	void SetScale(DirectX::SimpleMath::Vector3 scale);
	//�X�P�[���Z�b�g
	void SetRotate(DirectX::SimpleMath::Quaternion roteto);
	DirectX::SimpleMath::Quaternion GetRotate()const { return m_rotate; }
	//matrix�擾
	DirectX::SimpleMath::Matrix GetMatrix() const { return m_matrix; }
	//�ʕ`��Z�b�g
	void SetRender(std::function<void(const Camera&)> render);
	//�摗��`��t���O�Z�b�g
	void SetIsAfterDraw(bool isafterDraw) { m_isAfterRender = isafterDraw; }
	//�摗��`��t���O�擾
	bool GetIsAfterDraw()const { return m_isAfterRender; }
	//�e�����t���O�Z�b�g
	void SetIsShadow(bool isshadow) { m_isShadow = isshadow; }
	//�e�����t���O�擾
	bool GetIsShadow()const { return m_isShadow; }
	//�V�[���؂�ւ��C�x���g
	void LoadScene(Scene* scene);
};

