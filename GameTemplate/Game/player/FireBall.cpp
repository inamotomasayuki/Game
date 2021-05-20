#include "stdafx.h"
#include "FireBall.h"
#include "Player.h"

namespace {
	const float CHARACON_RADIUS = 5.0f;					//�L�����R���̔��a
	const float CHARACON_HIGHT = 5.0f;					//�L�����R���̍���
	const float DELTA_TIME = 1.0f / 60.0f;				//�o�ߎ��ԁ@�P�ʁF�b
	const float FIREBALL_GRAVITY = 1500.0f;				//�d��
	const float JUMP_SPEED_DECAY = 0.85f;				//�W�����v���x����
	const float PYON_SPEED = 800.0f;					//�҂��X�s�[�h
	const float JUMP_SPEED_ZERO_JUDGMENT = 200.0f;		//�W�����v���x���[���ɂ���l
	const float SPEED = 2000.0f;						//���x
	const CVector3 TARGET = { 0.0f, 100.0f, 0.0f };		//�^�[�Q�b�g
	const CVector3 POS = { 0.0f, 100.0f, 30.0f };		//�ʒu
	const CVector3 POS_RUN = { 0.0f, 100.0f, 40.0f };	//�ʒu
	const float DELETE_TIME = 300;						//�폜����
}
FireBall::FireBall()
{
	m_skinModel.Init(L"Assets/modelData/FireBall.cmo");
	//�t�@�C�A�{�[���𐶐�������W�����߂�
	{
		m_player = g_goMgr.FindGameObject<Player>("player");
		m_rotation = m_player->GetRotation();
		m_targetPos = m_player->GetPositon();
		m_targetPos.y += 10.0f;
		if (g_pad[0].IsPress(enButtonB)) {
			m_position = POS_RUN;
		}
		else {
			m_position = POS;
		}
		m_toPos = m_position - TARGET;
		m_rotation.Multiply(m_toPos);
		m_position = m_targetPos + m_toPos;
		m_vectorXZ = m_position - m_player->GetPositon();
		m_vectorXZ.y = 0.0f;
		m_vectorXZ.Normalize();
		m_vectorXZ *= SPEED;
	}
	//�L�����N�^�[�R���g���[���[������
	m_charaCon.Init(
		CHARACON_RADIUS,			//���a
		CHARACON_HIGHT,				//����
		m_position					//�������W
	);

}


FireBall::~FireBall()
{
}

void FireBall::Update()
{
	m_deleteTimer++;
	//��莞�Ԃō폜
	if (m_deleteTimer == DELETE_TIME) {
		g_goMgr.DeleteGameObject(this);
	}
	//�X�s�[�h
	m_moveSpeed = m_vectorXZ;
	//���˕Ԃ�
	if (m_charaCon.IsWallHit()) {
		m_moveSpeed = m_charaCon.GetReturnVector() * SPEED;
	}
	m_moveSpeed.y -= FIREBALL_GRAVITY;
	//�҂��҂��
	if (m_charaCon.IsOnGround()) {
		m_jumpSpeed = PYON_SPEED;
		m_isJump = true;
	}
	if (m_isJump == true) {
		m_moveSpeed.y = m_jumpSpeed;
		m_jumpSpeed *= JUMP_SPEED_DECAY;
		if (m_jumpSpeed < JUMP_SPEED_ZERO_JUDGMENT) {
			m_jumpSpeed = 0;
			m_isJump = false;
		}
	}
	m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);
	//���[���h�s��̍X�V�B
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void FireBall::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
}