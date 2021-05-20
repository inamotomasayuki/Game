#include "stdafx.h"
#include "Enemy02.h"
#include "Game.h"
#include "GameData.h"
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
	const float JUMP_SPEED_DECAY = 0.85f;				//�W�����v���x����
	const float PYON_SPEED = 2000.0f;					//�҂��X�s�[�h
	const int STOP_TIMER = 120;							//�����^�C�}�[�@�P�ʁF�b
	const float MOVE_SPEED_X = 400.0f;					//X�����̈ړ����x
	const float JUMP_SPEED_ZERO_JUDGMENT = 200.0f;		//�W�����v���x���[���ɂ���l
	const float DELTA_TIME = 1.0f / 60.0f;				//�o�ߎ��ԁ@�P�ʁF�b
	const float RIGHT_ANGLE = 90.0f;					//���p
	const float DEFAULT_GRAVITY = 200.0f;				//�d��
	const float	DAMAGE_GRAVITY = 500.0f;				//�d��
	const float SPRITE_W = 50.0f;			//�X�v���C�g��
	const float SPRITE_H = 50.0f;			//�X�v���C�g����
}

Enemy02::Enemy02()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_skinModel.Init(L"Assets/modelData/wingKuribo.cmo");
	m_fumuSE = g_goMgr.NewGameObject<CSoundSource>(0);
	m_fumuSE->Init(L"Assets/sound/fumu.wav");
	if (g_gameData.GetStageNo() != g_gameData.enStage_One) {
		//�E�����X�^�[�g�������_��
		auto random = rand() % enState_Num;
		if (random == enState_left) {
			m_state = enState_left;
		}
		else if (random == enState_right) {
			m_state = enState_right;
		}
	}
	else {
		m_state = enState_left;
	}
	m_sprite.Init(L"Assets/sprite/icon.dds", SPRITE_W, SPRITE_H);
	m_spriteBack.Init(L"Assets/sprite/icon.dds", SPRITE_W, SPRITE_H);
}

void Enemy02::Update()
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
			//��������
			Move();
			//�U��
			Attack();
		}
		//��]
		Rotation();
		//���S*�X�R�A�l
		Death(SCORE);
		DeathEnemyBallContact(SCORE);
		DeathFireBall(SCORE);

	}
}

void Enemy02::Move()
{
	float GRAVITY = DEFAULT_GRAVITY;
	//�U������ĂȂ��Ȃ�
	if (!m_isAttacked) {
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
		//����
		m_timer++;
		if (m_state == enState_right) {
			m_moveSpeed.x = MOVE_SPEED_X;
			if (m_timer == STOP_TIMER) {
				m_timer = 0;
				m_state = enState_left;
			}
		}
		if (m_state == enState_left) {
			m_moveSpeed.x = -MOVE_SPEED_X;
			if (m_timer == STOP_TIMER) {
				m_timer = 0;
				m_state = enState_right;
			}
		}
	}
	//�U�����ꂽ��
	else {
		m_moveSpeed = CVector3::Zero();
		GRAVITY = DAMAGE_GRAVITY;
	}
	//�d��
	m_moveSpeed.y -= GRAVITY;

	m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);
}
void Enemy02::Rotation()
{
	//���Ƃ��̃x�N�g������p�x�����߂ĉ�]������B
	auto moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));  //�p�x�����߂�֐�
}
void Enemy02::Attack()
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
				}
			}
		}
	}
}

void Enemy02::Death(int score)
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