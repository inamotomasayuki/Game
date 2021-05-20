#include "stdafx.h"
#include "EnemyBall.h"
#include "Game.h"

namespace {
	const float ATTACK_WAIT_TIME = 40.0f;				//攻撃したときの待ち時間
	const float DEGREE_NUM = 80.0f;						//角度　単位：degree
	const float LENGTH = 60.0f;							//プレイヤーとの距離
	const float PLAYER_JUMP_LENGTH = 80.0f;				//プレイヤーがジャンプした時との距離
	const int ATTACK_MINUS_PLAYER_HP = -1;				//攻撃時プレイヤーHPマイナス
	const float PLAYER_NOCKBACK_SPEED = 2500.0f;		//プレイヤーのノックバックスピード
	const float ENEMY_GRAVITY = 800.0f;					//重力
	const float ENEMY_GRAVITY_ACCELERATION = 1.02f;		//重力加速度
	const int SCORE = 0;								//スコア
	const float KICKED_SPEED = -2000.0f;				//蹴られた時のスピード（蹴った方向に飛ばすためにマイナス）
	const float DELTA_TIME = 1.0f / 60.0f;				//経過時間　単位：秒
	const float ROTATION_SPEED = 40.0f;					//回転速度
	const int DELETE_TIME = 200;						//削除時間
	const float SPRITE_W = 50.0f;			//スプライト幅
	const float SPRITE_H = 50.0f;			//スプライト高さ
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
		//プレイヤーに伸びるベクトル＆正規化
		VectorToPlayer();
		//角度を求める
		Angle();
		//攻撃
		Attack();
		//回転
		Rotation();
		//死亡*スコア値
		Death(SCORE);
		DeathFireBall(SCORE);
		m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);
	}

	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

void EnemyBall::Attack()
{
	//攻撃中じゃなかったら攻撃
	if (m_isBallAttack
		&& !m_isAttack) {
		if (fabs(m_angle) > CMath::DegToRad(DEGREE_NUM)
			&& m_len < LENGTH) {
			m_v.y = 0.0f;
			//ノックバックさせる速度
			m_player->SetAddSpeed(m_v * PLAYER_NOCKBACK_SPEED);
			m_player->SetIsAttacked(true);	//攻撃された。
			m_isAttack = true;	//攻撃した
			m_isBallAttack = false;
			m_player->SetIsDamageSE(true);
			if (!m_player->GetisItem()) {
				m_game->SetHP(ATTACK_MINUS_PLAYER_HP);
			}
		}
	}
	//攻撃したら少し待つ
	else {
		m_waitTimer++;
		if (m_waitTimer == ATTACK_WAIT_TIME) {
			m_waitTimer = 0;
			m_isAttack = false;		//攻撃してない。
		}
	}
}

void EnemyBall::Rotation()
{
	if (m_isKicked) {
		//一定速度で回転させる
		float rotSpeed = 0.0f;;
		rotSpeed += ROTATION_SPEED;
		CQuaternion addRot;
		addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
		m_rotation.Multiply(addRot);
	}
}

void EnemyBall::Death(int score)
{
	//攻撃受けてジャンプして離れたら
	if (m_len > PLAYER_JUMP_LENGTH) {
		m_isPlayerJump = true;		//いったん離れた
	}
	//玉状態処理
	Ball();
	//削除
	if (m_isKicked) {
		m_deleteTimer++;
		if (m_deleteTimer >= DELETE_TIME) {
			g_goMgr.DeleteGameObject(this);
		}
	}
}

void EnemyBall::Ball()
{
	//再度近づいたら
	if (m_isPlayerJump
		&& m_len < LENGTH
		&& !m_charaCon.IsWallHit()) {
		m_v.y = 0.0f;
		//ノックバック
		m_moveSpeed = m_v * KICKED_SPEED;
		m_pokoSE->Play(false);
		m_isKicked = true;
		m_isApproachAgain = true;
	}		
	if (m_charaCon.IsWallHit()) {
		m_moveSpeed = m_charaCon.GetReturnVector() * -KICKED_SPEED;
	}
	//再々度近づいたら
	if (m_isApproachAgain
		&& m_len > PLAYER_JUMP_LENGTH) {
		m_isBallAttack = true;
	}

	//重力
	if (!m_charaCon.IsOnGround()) {
		m_gravity *= ENEMY_GRAVITY_ACCELERATION;
		m_moveSpeed.y -= m_gravity;
	}
}
