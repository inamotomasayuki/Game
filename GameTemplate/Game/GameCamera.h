#pragma once
#include "player/Player.h"
class Game;
class GameCamera final : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	/*!
	*@brief �X�V
	*/
	void Update() override;
	/*!
	*@brief �`��
	*/
	void Draw() override {}
private:
	/*!
	*@brief �J�������l��������]
	*/
	void Rotation();
	/*!
	*@brief �Y�[���C���E�A�E�g
	*/
	void ZoomInAndOut();
	/*!
	*@brief �X�e�[�W�P�J����
	*/
	void StageOneCamera();
	/*!
	*@brief �Q�[���N���A�J����
	*/
	void GameClearCamera();
	/*!
	*@brief �Q�[���I�[�o�[�J����
	*/
	void GameOverCamera();
private:	
	Player* m_player = nullptr;				//�v���C���[
	Game* m_game = nullptr;					//�Q�[��
	CVector3 m_cameraPos;					//���_
	CVector3 m_cameraTarget;				//�����_
	CVector3 m_toCameraPos;					//���W
	CVector3 m_oldPos;						//�O�̍��W	
	CVector3 m_nextCameraPos;				//���̍��W
	CVector3 m_clearPos = CVector3::Zero();	//�N���A�J�����ʒu
	CVector3 m_moveSpeed;					//�ړ����x
	CQuaternion m_rotation;					//��]
	bool m_isButtonYoko = false;			//��������
	bool m_isButtonMae = false;				//�O������
	bool m_isStop = false;					//�~�߂�
	bool m_isClearCameraInit = false;		//�N���A�J����������
};

