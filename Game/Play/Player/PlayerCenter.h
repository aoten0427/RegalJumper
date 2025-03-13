// ================================================================ 
// �t�@�C���� :PlayerCenter.h 
// �쐬�� : �i�R�ɓV
// ���� :  �v���C���[�Ɋ֌W������̂��Ǘ�
// ================================================================
#pragma once
#include"Base/Object/Object.h"

class Player;
class Thread;
class Target;
class Search;

class PlayerCenter:public Object
{
private:
	//�v���C���[
	Player* m_player;
	//��
	Thread* m_thread;
	//�T�[�`���[
	Search* m_search;
public:
	//�R���X�g���N�^
	PlayerCenter(Scene* scene);
	//�f�X�g���N�^
	~PlayerCenter()override = default;
	//�A�b�v�f�[�g
	void ObjectUpdate(float deltatime)override;
	//������
	void ThreadShot(DirectX::SimpleMath::Vector3 direction);
};
