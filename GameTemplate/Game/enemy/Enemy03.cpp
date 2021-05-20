#include "stdafx.h"
#include "Enemy03.h"
#include "Game.h"
#include "GameData.h"

namespace {
	const int ATTACK_WAIT_TIME = 40;				//�U�������Ƃ��̑҂�����
	const float ATTACKED_WAIT_TIME = 20.0f;			//�U�����ꂽ�Ƃ��̑҂�����
	const float DEGREE_NUM = 80.0f;					//�p�x�@�P�ʁFdegree
	const float LENGTH = 60.0f;						//�v���C���[�Ƃ̋���
	const float PLAYER_JUMP_LENGTH = 80.0f;			//�v���C���[���W�����v�������Ƃ̋���
	const int ATTACK_MINUS_PLAYER_HP = -1;			//�U�����v���C���[HP�}�C�i�X
	const float PLAYER_NOCKBACK_SPEED = 2500.0f;	//�v���C���[�̃m�b�N�o�b�N�X�s�[�h
	const float ENEMY_GRAVITY = 10.0f;				//�d��
	const float GRAVITY_ACCELERATION = 1.1f;		//�d�͉���
	const float GRAVITY_UPPER = 400.0f;				//�d�͏��
	const int SCORE = 0;							//�X�R�A
	const float KICKED_SPEED = -2000.0f;			//�R��ꂽ���̃X�s�[�h�i�R���������ɔ�΂����߂Ƀ}�C�i�X�j
	const float DELTA_TIME = 1.0f / 60.0f;			//�o�ߎ��ԁ@�P�ʁF�b
	const float ROTATION_SPEED = 40.0f;				//��]���x
	const float DELETE_LENGTH = 100000.0f;			//�폜����
	const float ANGLE = 100.0f;						//�p�x
	const float PETTANKO_SCALE_Z = 10.0f;				//�؂�����
	const float MOVE_SPEED = 150.0f;				//�ړ����x
	const float SPRITE_W = 50.0f;			//�X�v���C�g��
	const float SPRITE_H = 50.0f;			//�X�v���C�g����
}

Enemy03::Enemy03()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_skinModel.Init(L"Assets/modelData/turtle.cmo");
	m_gravity = ENEMY_GRAVITY;
	m_fumuSE = g_goMgr.NewGameObject<CSoundSource>(0);
	m_fumuSE->Init(L"Assets/sound/fumu.wav");
	m_sprite.Init(L"Assets/sprite/icon.dds", SPRITE_W, SPRITE_H);
	m_spriteBack.Init(L"Assets/sprite/icon.dds", SPRITE_W, SPRITE_H);
}

void Enemy03::Update()
{
	m_player = g_goMgr.FindGameObject<Player>("player");
	m_game = g_goMgr.FindGameObject<Game>("game");

	//���[���h�s��̍X�V�B
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	if (m_player != nullptr
		&& m_game != nullptr
		&& !m_game->GetStar()) {
		//�v���C���[�ɐL�т�x�N�g�������K��
		VectorToPlayer();
		//�p�x�����߂�
		Angle();
		//�U��
		Attack();
		//��]
		Rotation();
		if (g_gameData.GetStageNo() == 0) {
			//�p�X�ړ�
			PassMove();
		}
		//���S*�X�R�A�l
		Death(SCORE);
		DeathEnemyBallContact(SCORE);
		DeathFireBall(SCORE);
		m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);
	}
}
void Enemy03::PassMove()
{
	//�p�X�ړ�
	const CVector3& diff = m_point->s_position - m_position;
	if (diff.Length() <= 20.0f) {
		if (m_point->s_number == m_pointList.size()) {
			m_point = &m_pointList[0];
		}
		//�����łȂ��Ȃ�z��̎��̗v�f�̃|�C���g��ړI�n�Ƃ���
		else {
			m_point = &m_pointList[m_point->s_number];
		}
	}
	m_moveSpeed = m_point->s_position - m_position;
	m_moveSpeed.Normalize();
	m_moveSpeed *= MOVE_SPEED;
}
void Enemy03::Rotation()
{
	if (!m_isKicked) {
		//���Ƃ��̃x�N�g������p�x�����߂ĉ�]������B
		auto moveSpeedXZ = m_moveSpeed;
		moveSpeedXZ.y = 0.0f;
		moveSpeedXZ.Normalize();
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));  //�p�x�����߂�֐�
	}
	else {
		//��葬�x�ŉ�]������
		float rotSpeed = 0.0f;;
		rotSpeed += ROTATION_SPEED;
		CQuaternion addRot;
		addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
		m_rotation.Multiply(addRot);
	}
}
void Enemy03::Attack()
{
	if (!m_isAttacked) {
		if (!m_player->IsHipDrop()) {
			//�U��������Ȃ�������U��
			if (!m_isAttacked
				|| (m_isAttacked && m_isBallAttack)
				&& !m_isAttack) {
				if (fabs(m_angle) > CMath::DegToRad(DEGREE_NUM)
					&& m_len < LENGTH) {
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

void Enemy03::Death(int score)
{
	if (!m_player->IsHipDrop()) {
		//�U������ĂȂ�������
		if (m_isAttacked == false) {
			if (fabs(m_angle) <= CMath::DegToRad(DEGREE_NUM) && m_len < LENGTH) {
				m_player->SetJumpFlag(true);	//�W�����v������	
				m_fumuSE->Play(false);
				m_game->SetScore(score);		//�X�R�A
				m_isAttacked = true;		//�U�����ꂽ
			}
		}
		if (!m_isHipDrop) {
			if (m_isAttacked) {
				m_enemyBall = g_goMgr.NewGameObject<EnemyBall>("enemyBall");
				m_enemyBall->SetPosition(m_position);
				m_enemyBall->InitCharaCon(m_position);
				g_goMgr.DeleteGameObject(this);
			}
		}
	}
	else {
		//�U������ĂȂ�������
		if (m_isAttacked == false) {
			if (fabs(m_angle) <= CMath::DegToRad(ANGLE) && m_len < LENGTH) {
				m_scale.z /= PETTANKO_SCALE_Z;
				m_fumuSE->Play(false);
				m_isHipDrop = true;
				m_isAttacked = true;		//�U�����ꂽ
			}
		}
	}
	//�q�b�v�h���b�v
	if (m_isHipDrop) {
		if (m_isAttacked) {
			m_waitTimer++;
			m_moveSpeed = CVector3::Zero();
			if (m_waitTimer == ATTACKED_WAIT_TIME) {
				m_game->SetScore(score);
				g_goMgr.DeleteGameObject(this);
			}
		}
	}
}
