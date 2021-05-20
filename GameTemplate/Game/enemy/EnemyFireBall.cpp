#include "stdafx.h"
#include "EnemyFireBall.h"
#include "../Game.h"

namespace {
	const float DEGREE_NUM = 30.0f;						//�p�x�@�P�ʁFdegree
	const float LENGTH = 70.0f;							//�v���C���[�Ƃ̋���
	const int ATTACK_MINUS_PLAYER_HP = -1;				//�U�����v���C���[HP�}�C�i�X
	const float PLAYER_NOCKBACK_SPEED = 2500.0f;		//�v���C���[�̃m�b�N�o�b�N�X�s�[�h
	const float MOVE_SPEED = 10.0f;						//�t�@�C�A�{�[���ړ����x
	const int DLETE_TIME = 300;							//�폜����
}

EnemyFireBall::EnemyFireBall()
{
	m_skinModel.Init(L"Assets/modelData/FireBall.cmo");
}


EnemyFireBall::~EnemyFireBall()
{
}

void EnemyFireBall::Update()
{
	m_player = g_goMgr.FindGameObject<Player>("player");
	if (m_player != nullptr) {
		m_position += m_vector * MOVE_SPEED;
		//�U��
		Attack();
	}
	//�폜����
	Delete();
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

void EnemyFireBall::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//�������C�g�I�t
	m_skinModel.RimLightOff();
	//�V���h�E���V�[�o�[�I�t
	m_skinModel.ShadowReciverOff();
}

void EnemyFireBall::Attack()
{
	//���������߂�
	auto vec = m_player->GetPositon() - m_position;
	auto len = vec.Length();
	vec.Normalize();
	// �p�x�����߂�
	auto naiseki = vec.Dot(CVector3::AxisY());
	auto angle = acos(naiseki);
	

	const auto& game = g_goMgr.FindGameObject<Game>("game");
	if (!m_isAttack) {
		if (len < LENGTH) {
			//�������_���[�W
			m_player->SetIsAchichi();
			m_player->SetAchichiVec(vec);
			m_isAttack = true;
			if (!m_player->GetisItem()) {
				game->SetHP(ATTACK_MINUS_PLAYER_HP);
			}
		}
	}
}

void EnemyFireBall::Delete()
{
	m_deleteTimer++;
	if (m_deleteTimer == DLETE_TIME) {
		g_goMgr.DeleteGameObject(this);
	}
	if (m_isAttack) {
		g_goMgr.DeleteGameObject(this);
	}
}