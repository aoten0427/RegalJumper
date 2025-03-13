// ================================================================ 
// �t�@�C���� : Option.h
// �쐬�� : �i�R�ɓV
// ���� :  �I�v�V����
// ================================================================

#pragma once
#include"Base/Canvas/UserInterface/UserInterface.h"
#include"Base/Scene/Scene.h"


class Tween;
template<typename...Args>
class Subject;
class OptionContents;
class OptionExit;


class Option :public UserInterface
{
private:
	static constexpr int SELECT_NUM = 3;

	//�I����
	enum class SELECT
	{
		BGM,
		SE,
		SENSITIVITY
	};
public:
	float GetSensitivity() const { return m_sensitivity; }
private:
	//���O���
	Scene::State m_oldSceneState;
	//�傫��
	DirectX::SimpleMath::Vector2 m_size;
	//�J�pTween
	Tween* m_tween;
	//�J�������̎���Subject
	Subject<>* m_openSubject;
	//�����Ƃ���Subject
	Subject<>* m_closeSubject;
	//�ύX���e
	OptionContents* m_contents[SELECT_NUM];
	//�����p�[�Z���g�i�[
	float m_initialParcent[SELECT_NUM];
	//�ޏo�{�^��
	OptionExit* m_exitButton;
	//���x
	float m_sensitivity;
public:
	//�R���X�g���N�^
	Option(Canvas* canvas);
	~Option()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
	//�I������
	void Finalize()override;
	//�J��
	void Open();
	//����
	void Close();
private:
	void LoadData();
	void WriteData();
};