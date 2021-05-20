#include "stdafx.h"
#include "EnemyBall.h"
#include "Game.h"

namespace {
	const float ATTACK_WAIT_TIME = 40.0f;				//�U�������Ƃ��̑҂�����
	const float DEGREE_NUM = 80.0f;						//�p�x�@�P�ʁFdegree
	const float LENGTH = 60.0f;							//�v���C���[�Ƃ̋���
	const float PLAYER_JUMP_LENGTH = 80.0f;				//�v���C���[���W�����v�������Ƃ̋���
	const int ATTACK_MINUS_PLAYER_HP = -1;				//�U�����v���C���[HP�}�C�i�X
	const float PLAYER_NOCKBACK_SPEED = 2500.0f;		//�v���C���[�̃m�b�N�o�b�N�X�s�[�h
	const float ENEMY_GRAVITY = 800.0f;					//�d��
	const float ENEMY_GRAVITY_ACCELERATION = 1.02f;		//�d�͉����x
	const int SCORE = 0;								//�X�R�A
	const float KICKED_SPEED = -2000.0f;				//�R��ꂽ���̃X�s�[�h�i�R���������ɔ�΂����߂Ƀ}�C�i�X�j
	const float DELTA_TIME = 1.0f / 60.0f;				//�o�ߎ��ԁ@�P�ʁF�b
	const float ROTATION_SPEED = 40.0f;					//��]���x
	const int DELETE_TIME = 200;						//�폜����
	const float SPRITE_W = 50.0f;			//�X�v���C�g��
	const float SPRITE_H = 50.0f;			//�X�v���C�g����
}

EnemyBall::EnemyBall()
{
	m_skinModel.Init(L"Assets/modelData/turtleShell.cmo");
	m_gravity = ENEMY_GRAVITY;
	m_pokoSE = g_goMgr.NewGameObject<CSoundSource>(0);
	m_pokoSE->Init(L"Assets/sound/poko.wav");
	m_sprite.Init(L"Assets/sprite/icon.dds", SPRITE_W, SPRITE_H);
	m_spriteBack.Init(L"Assets/sprite/icon.dds", SPRITE_W, SPRITE_H);
}

void EnemyBall::Update()
{
	m_player = g_goMgr.FindGameObject<Player>("player");
	m_game = g_goMgr.FindGameObject<Game>("game");

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
		//���S*�X�R�A�l
		Death(SCORE);
		DeathFireBall(SCORE);
		m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);
	}

	//���[���h�s��̍X�V�B
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

void EnemyBall::Attack()
{
	//�U��������Ȃ�������U��
	if (m_isBallAttack
		&& !m_isAttack) {
		if (fabs(m_angle) > CMath::DegToRad(DEGREE_NUM)
			&& m_len < LENGTH) {
			m_v.y = 0.0f;
			//�m�b�N�o�b�N�����鑬�x
			m_player->SetAddSpeed(m_v * PLAYER_NOCKBACK_SPEED);
			m_player->SetIsAttacked(true);	//�U�����ꂽ�B
			m_isAttack = true;	//�U������
			m_isBallAttack = false;
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

void EnemyBall::Rotation()
{
	if (m_isKicked) {
		//��葬�x�ŉ�]������
		float rotSpeed = 0.0f;;
		rotSpeed += ROTATION_SPEED;
		CQuaternion addRot;
		addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
		m_rotation.Multiply(addRot);
	}
}

void EnemyBall::Death(int score)
{
	//�U���󂯂ăW�����v���ė��ꂽ��
	if (m_len > PLAYER_JUMP_LENGTH) {
		m_isPlayerJump = true;		//�������񗣂ꂽ
	}
	//�ʏ�ԏ���
	Ball();
	//�폜
	if (m_isKicked) {
		m_deleteTimer++;
		if (m_deleteTimer >= DELETE_TIME) {
			g_goMgr.DeleteGameObject(this);
		}
	}
}

void EnemyBall::Ball()
{
	//�ēx�߂Â�����
	if (m_isPlayerJump
		&& m_len < LENGTH
		&& !m_charaCon.IsWallHit()) {
		m_v.y = 0.0f;
		//�m�b�N�o�b�N
		m_moveSpeed = m_v * KICKED_SPEED;
		m_pokoSE->Play(false);
		m_isKicked = true;
		m_isApproachAgain = true;
	}		
	if (m_charaCon.IsWallHit()) {
		m_moveSpeed = m_charaCon.GetReturnVector() * -KICKED_SPEED;
	}
	//�āX�x�߂Â�����
	if (m_isApproachAgain
		&& m_len > PLAYER_JUMP_LENGTH) {
		m_isBallAttack = true;
	}

	//�d��
	if (!m_charaCon.IsOnGround()) {
		m_gravity *= ENEMY_GRAVITY_ACCELERATION;
		m_moveSpeed.y -= m_gravity;
	}
}
