// ================================================================ 
// �t�@�C���� : SelectScene.h
// �쐬�� : �i�R�ɓV
// ���� :  �Z���N�g�V�[��
// ================================================================

#pragma once
#include"Base/Scene/Scene.h"

class SelectScene :public Scene
{
public:
	Camera* GetCamera()const { return m_camera; }
	Canvas* GetCanvas()const { return m_canvas; }
private:
	//�J����
	Camera* m_camera;
	//�L�����o�X
	Canvas* m_canvas;
public:
	//�R���X�g���N�^
	SelectScene(CommonResources* resources);
	//�f�X�g���N�^
	~SelectScene()override = default;
	//�A�b�v�f�[�g
	void SceneUpdate(float deltatime)override;
	//�V�[��ID�擾
	SceneID GetSceneID() { return SceneID::SELECT; }
};