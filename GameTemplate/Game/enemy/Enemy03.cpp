#include "stdafx.h"
#include "Enemy03.h"
#include "Game.h"
#include "GameData.h"

namespace {
	const int ATTACK_WAIT_TIME = 40;				//攻撃したときの待ち時間
	const float ATTACKED_WAIT_TIME = 20.0f;			//攻撃されたときの待ち時間
	const float DEGREE_NUM = 80.0f;					//角度　単位：degree
	const float LENGTH = 60.0f;						//プレイヤーとの距離
	const float PLAYER_JUMP_LENGTH = 80.0f;			//プレイヤーがジャンプした時との距離
	const int ATTACK_MINUS_PLAYER_HP = -1;			//攻撃時プレイヤーHPマイナス
	const float PLAYER_NOCKBACK_SPEED = 2500.0f;	//プレイヤーのノックバックスピード
	const float ENEMY_GRAVITY = 10.0f;				//重力
	const float GRAVITY_ACCELERATION = 1.1f;		//重力加速
	const float GRAVITY_UPPER = 400.0f;				//重力上限
	const int SCORE = 0;							//スコア
	const float KICKED_SPEED = -2000.0f;			//蹴られた時のスピード（蹴った方向に飛ばすためにマイナス）
	const float DELTA_TIME = 1.0f / 60.0f;			//経過時間　単位：秒
	const float ROTATION_SPEED = 40.0f;				//回転速度
	const float DELETE_LENGTH = 100000.0f;			//削除距離
	const float ANGLE = 100.0f;						//角度
	const float PETTANKO_SCALE_Z = 10.0f;				//ぺったんこ
	const float MOVE_SPEED = 150.0f;				//移動速度
	const float SPRITE_W = 50.0f;			//スプライト幅
	const float SPRITE_H = 50.0f;			//スプライト高さ
}

Enemy03::Enemy03()
{
	//cmoファイルの読み込み。
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

	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

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
		if (g_gameData.GetStageNo() == 0) {
			//パス移動
			PassMove();
		}
		//死亡*スコア値
		Death(SCORE);
		DeathEnemyBallContact(SCORE);
		DeathFireBall(SCORE);
		m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);
	}
}
void Enemy03::PassMove()
{
	//パス移動
	const CVector3& diff = m_point->s_position - m_position;
	if (diff.Length() <= 20.0f) {
		if (m_point->s_number == m_pointList.size()) {
			m_point = &m_pointList[0];
		}
		//そうでないなら配列の次の要素のポイントを目的地とする
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
		//ｘとｚのベクトルから角度を求めて回転させる。
		auto moveSpeedXZ = m_moveSpeed;
		moveSpeedXZ.y = 0.0f;
		moveSpeedXZ.Normalize();
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));  //角度を求める関数
	}
	else {
		//一定速度で回転させる
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
			//攻撃中じゃなかったら攻撃
			if (!m_isAttacked
				|| (m_isAttacked && m_isBallAttack)
				&& !m_isAttack) {
				if (fabs(m_angle) > CMath::DegToRad(DEGREE_NUM)
					&& m_len < LENGTH) {
					m_v.y = 0.0f;
					//ノックバックさせる速度
					m_player->SetAddSpeed(m_v * PLAYER_NOCKBACK_SPEED);
					m_player->SetIsAttacked(true);	//攻撃された。
					m_isAttack = true;	//攻撃した。	
					m_player->SetIsDamageSE(true);
					if (!m_player->GetisItem()) {
						m_game->SetHP(ATTACK_MINUS_PLAYER_HP);
					}
				}
			}
			//攻撃したら少し待つ
			if (m_isAttack) {
				m_waitTimer++;
				if (m_waitTimer == ATTACK_WAIT_TIME) {
					m_waitTimer = 0;
					m_isAttack = false;		//攻撃してない。
				}
			}
		}
	}
}

void Enemy03::Death(int score)
{
	if (!m_player->IsHipDrop()) {
		//攻撃されてなかったら
		if (m_isAttacked == false) {
			if (fabs(m_angle) <= CMath::DegToRad(DEGREE_NUM) && m_len < LENGTH) {
				m_player->SetJumpFlag(true);	//ジャンプさせる	
				m_fumuSE->Play(false);
				m_game->SetScore(score);		//スコア
				m_isAttacked = true;		//攻撃された
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
		//攻撃されてなかったら
		if (m_isAttacked == false) {
			if (fabs(m_angle) <= CMath::DegToRad(ANGLE) && m_len < LENGTH) {
				m_scale.z /= PETTANKO_SCALE_Z;
				m_fumuSE->Play(false);
				m_isHipDrop = true;
				m_isAttacked = true;		//攻撃された
			}
		}
	}
	//ヒップドロップ
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
