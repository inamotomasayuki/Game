#include "stdafx.h"
#include "Enemy01.h"
#include "Game.h"

namespace {
	const float LENGTH_UPPER = 900.0f;				//�ǐՏ������
	const float LENGTH_UNDER = 50.0f;				//�ǐՉ�������
	const float MOVE_SPEED = 400.0f;				//�ړ����x
	const float MINIMUM = 0.0001f;					//�ɏ�
	const float DELTA_TIME = 1.0f / 60.0f;			//�o�ߎ��ԁ@�P�ʁF�b
	const float MOVE_STOP = 0.01f;					//�~�܂�
	const float INIT_POS_LEN = 10.0f;				//���^�[�����̏����ʒu�Ƃ̋���
	const int ATTACK_WAIT_TIME = 40;				//�U�������Ƃ��̑҂�����
	const float ATTACKED_WAIT_TIME = 20.0f;			//�U�����ꂽ�Ƃ��̑҂�����
	const float SCALE_DIVISION_Z = 2.0f;			//�X�P�[�������鐔�l
	const float PECHANKO_SCALE_Z = 10.0f;			//�؂���񂱂ɂ���̂Ɋ��鐔�l
	const float DEGREE_NUM = 80.0f;					//�p�x�@�P�ʁFdegree
	const float RIGHT_ANGLE = 100.0f;				//���p
	const float LENGTH = 50.0f;						//�v���C���[�Ƃ̋���
	const int ATTACK_MINUS_PLAYER_HP = -1;			//�U�����v���C���[HP�}�C�i�X
	const float PLAYER_NOCKBACK_SPEED = 2500.0f;	//�v���C���[�̃m�b�N�o�b�N�X�s�[�h
	const int SCORE = 0;					//�X�R�A
	const float SPRITE_W = 50.0f;			//�X�v���C�g��
	const float SPRITE_H = 50.0f;			//�X�v���C�g����
}

Enemy01::Enemy01()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_skinModel.Init(L"Assets/modelData/UCW_Kuribo.cmo");
	m_fumuSE = g_goMgr.NewGameObject<CSoundSource>(0);
	m_fumuSE->Init(L"Assets/sound/fumu.wav");
	m_sprite.Init(L"Assets/sprite/icon.dds", SPRITE_W, SPRITE_H);
	m_spriteBack.Init(L"Assets/sprite/icon.dds", SPRITE_W, SPRITE_H);
}

void Enemy01::Update()
{
	m_player = g_goMgr.FindGameObject<Player>("player");
	m_game = g_goMgr.FindGameObject<Game>("game");

	//���[���h�s��̍X�V�B
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	if (m_player != nullptr
		&& m_game != nullptr
		&& !m_game->GetGameOverFlag()
		&& !m_game->GetStar()) {
		//�v���C���[�ɐL�т�x�N�g�������K��
		VectorToPlayer();
		//�p�x�����߂�
		Angle();
		auto warp = g_goMgr.FindGameObject<Warp>("warp");
		if (!m_isDeath) {
			if (!warp->IsWarp()) {
				//�ǐ�
				Search();
				//�U���i�v���C���[���m�b�N�o�b�N�j
				Attack();
			}
			else {
				m_moveSpeed = m_v * MOVE_STOP;
			}
			//���̈ʒu�ɖ߂�
			Return();
		}
		m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);

		//��]
		Rotation();
		//���S
		Death(SCORE);
		DeathEnemyBallContact(SCORE);
		DeathFireBall(SCORE);
	}
}
void Enemy01::Search()
{
	//�U�����Ă��Ȃ����U�����󂯂Ă��Ȃ�
	if (m_isAttack == false
		&& m_isAttacked == false) {
		//���L�̋����͈̔͂Ȃ炩�v���C���[���U�����󂯂Ă��Ȃ�������
		if (m_len > LENGTH_UNDER
			&& m_len < LENGTH_UPPER
			&& m_player->GetIsAttacked() == false) {
			//�v���C���[��ǐ�
			m_moveSpeed = m_v * MOVE_SPEED;
			m_moveSpeed.y = 0.0f;
		}
		else {
			//�ǐՂ��Ȃ��B
			//��]�����邽�߂ɂO�ł͂Ȃ��B
			m_moveSpeed = m_v * MINIMUM;
		}
	}
}
void Enemy01::Return()
{
	//���L�̋����͈̔͂Ȃ�
	if (m_len > LENGTH_UPPER) {
		auto initPos = m_initialPos - m_position;
		auto len = initPos.Length();
		initPos.Normalize();
		if (len < INIT_POS_LEN) {
			//�߂����瓮���Ȃ�
			m_moveSpeed = CVector3::Zero();
		}
		else {
			//���̈ʒu�ɖ߂�
			m_moveSpeed = initPos * MOVE_SPEED;
		}
	}
}
void Enemy01::Rotation()
{
	//���Ƃ��̃x�N�g������p�x�����߂ĉ�]������B
	auto moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));  //�p�x�����߂�֐�
}
void Enemy01::Attack()
{
	if (!m_isAttacked) {
		if (!m_player->IsHipDrop()) {
			//�U��������Ȃ�������U��
			if (m_isAttack == false) {
				if (fabs(m_angle) > CMath::DegToRad(DEGREE_NUM) && m_len < LENGTH) {
					m_v.y = 0.0f;
					//�m�b�N�o�b�N�����鑬�x
					m_player->SetAddSpeed(m_v * PLAYER_NOCKBACK_SPEED);
					m_player->SetIsAttacked(true);	//�U�����ꂽ�B
					m_isAttack = true;	//�U�������B
					m_player->SetIsDamageSE(true);
					if (!m_player->GetisItem()) {
						m_game->SetHP(ATTACK_MINUS_PLAYER_HP);
					}
				}
			}
			//�U�������班���҂�
			if (m_isAttack) {
				m_waitTimer++;
				if (m_waitTimer == ATTACK_WAIT_TIME) {
					m_waitTimer = 0;
					m_isAttack = false;		//�U�����ĂȂ��B
				}
			}
		}
	}
}

void Enemy01::Death(int score)
{
	if (!m_player->IsHipDrop()) {
		//�U������ĂȂ�������
		if (m_isAttacked == false) {
			if (fabs(m_angle) <= CMath::DegToRad(DEGREE_NUM) && m_len < LENGTH) {
				m_scale.z /= SCALE_DIVISION_Z;
				m_player->SetJumpFlag(true);	//�W�����v������
				m_fumuSE->Play(false);
				m_isAttacked = true;		//�U�����ꂽ
			}
		}
		//�U�����ꂽ�班���҂��Ă���폜
		if (m_isAttacked == true) {
			m_waitTimer++;
			if (m_waitTimer == ATTACKED_WAIT_TIME) {
				m_game->SetScore(score);
				g_goMgr.DeleteGameObject(this);
			}
		}
	}
	else {
		//�U������ĂȂ�������
		if (m_isAttacked == false) {
			if (fabs(m_angle) <= CMath::DegToRad(RIGHT_ANGLE) && m_len < LENGTH) {
				m_scale.z /= PECHANKO_SCALE_Z;
				m_fumuSE->Play(false);
				m_isAttacked = true;		//�U�����ꂽ
			}
		}
		//�U�����ꂽ�班���҂��Ă���폜
		if (m_isAttacked == true) {
			m_waitTimer++;
			if (m_waitTimer == ATTACKED_WAIT_TIME) {
				m_game->SetScore(score);
				g_goMgr.DeleteGameObject(this);
			}
		}
	}
}