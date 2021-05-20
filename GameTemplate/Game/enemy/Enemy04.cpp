#include "stdafx.h"
#include "Enemy04.h"
#include "Game.h"
#include "EnemyFireBall.h"

namespace {
	const int ATTACK_WAIT_TIME = 40;					//�U�������Ƃ��̑҂�����
	const float ATTACKED_WAIT_TIME = 20.0f;				//�U�����ꂽ�Ƃ��̑҂�����
	const float SCALE_DIVISION_Z = 2.0f;				//�X�P�[�������鐔�l
	const float PECHANKO_SCALE_Z = 10.0f;				//�؂���񂱂ɂ���̂Ɋ��鐔�l
	const float DEGREE_NUM = 80.0f;						//�p�x�@�P�ʁFdegree
	const float LENGTH = 50.0f;							//�v���C���[�Ƃ̋���
	const int ATTACK_MINUS_PLAYER_HP = -1;				//�U�����v���C���[HP�}�C�i�X
	const float PLAYER_NOCKBACK_SPEED = 2500.0f;		//�v���C���[�̃m�b�N�o�b�N�X�s�[�h
	const int SCORE = 0;								//�X�R�A
	const float RIGHT_ANGLE = 90.0f;					//���p
	const float FIRE_GENERATE_LENGTH_MAX = 600.0f;		//�t�@�C�A�[�����������
	const float FIRE_GENERATE_LENGTH_MIN = 150.0f;		//�t�@�C�A�[������������
	const int FIRE_GENERATE_INTERVAL = 70;				//�t�@�C�A�[�搶�Ԋu
	const float FIRE_GENERATE_POS_Y = 50.0f;			//�t�@�C�A�[����Y�ʒu
	const float FIRE_GENERATE_ANGLE = 40.0f;			//�t�@�C�A�[�����p�x

	const float VIEW_BOLUME_WIDTH = 1280.0f;		//�r���[�{�����[���̕�
	const float VIEW_BOLUME_HIGHT = 720.0f;			//�r���[�{�����[���̍���
	const float F_NEAR = 0.1f;						//�ߕ���
	const float F_FAR = 100.0f;						//������
	const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//�J�����̈ʒu
	const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//�J�����̒����_
	const CVector3 CAMERA_UP = { 0,1,0 };				//�J�����̏����

	const float SPRITE_W = 50.0f;			//�X�v���C�g��
	const float SPRITE_H = 50.0f;			//�X�v���C�g����

}

Enemy04::Enemy04()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_skinModel.Init(L"Assets/modelData/unityChan.cmo");
	m_fumuSE = g_goMgr.NewGameObject<CSoundSource>(0);
	m_fumuSE->Init(L"Assets/sound/fumu.wav");
	m_fireSE = g_goMgr.NewGameObject<CSoundSource>(0);
	m_fireSE->Init(L"Assets/sound/fire.wav");
	m_sprite.Init(L"Assets/sprite/icon.dds", SPRITE_W, SPRITE_H);
	m_spriteBack.Init(L"Assets/sprite/icon.dds", SPRITE_W, SPRITE_H);
}

void Enemy04::Update()
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
		if (!m_isDeath) {
			//�U��
			Attack();
		}
		//�t�@�C�A�{�[������
		FireBallGenerate();
		//��]
		Rotation();
		//���S*�X�R�A�l
		Death(SCORE);
		DeathEnemyBallContact(SCORE);
		DeathFireBall(SCORE);
	}	
}

void Enemy04::Rotation()
{
	if (!m_player->IsOnGround() && fabs(m_angle) < CMath::DegToRad(FIRE_GENERATE_ANGLE)) {
		return;
	}
	else if (m_len <= FIRE_GENERATE_LENGTH_MAX) {
		//���Ƃ��̃x�N�g������p�x�����߂ĉ�]������B
		auto moveSpeedXZ = m_player->GetPositon() - m_position;
		moveSpeedXZ.y = 0.0f;
		moveSpeedXZ.Normalize();
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));  //�p�x�����߂�֐�
	}
}
void Enemy04::Attack()
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
			else {
				m_waitTimer++;
				if (m_waitTimer == ATTACK_WAIT_TIME) {
					m_waitTimer = 0;
					m_isAttack = false;		//�U�����ĂȂ��B
					m_player->SetIsAttacked(false);		//�U������ĂȂ��B
				}
			}
		}
	}
}

void Enemy04::Death(int score)
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

void Enemy04::FireBallGenerate()
{
	if (!m_player->GetIsAttacked()) {
		if (fabs(m_angle) >= CMath::DegToRad(FIRE_GENERATE_ANGLE)
			&& m_len <= FIRE_GENERATE_LENGTH_MAX
			&& m_len >= FIRE_GENERATE_LENGTH_MIN) {
			m_isFireBallGenerate = true;
		}
		else {
			m_isFireBallGenerate = false;
		}
		if (m_isFireBallGenerate) {
			if (m_fireGenerateTimer == 0) {
				//�v���C���[�ւ̌��������߂�
				auto vecToPlayer = m_player->GetPositon() - m_position;
				vecToPlayer.Normalize();
				auto pos = m_position;
				pos.y += FIRE_GENERATE_POS_Y;			//�����グ��
				//����
				const auto& fireBall = g_goMgr.NewGameObject<EnemyFireBall>("enemyFireBall");
				fireBall->SetPosition(pos);
				fireBall->SetVector(vecToPlayer);
				m_fireSE->Play(false);
			}
			//�����Ԋu
			m_fireGenerateTimer++;
			if (m_fireGenerateTimer >= FIRE_GENERATE_INTERVAL) {
				m_fireGenerateTimer = 0;
			}
		}
	}
}