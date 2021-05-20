#include "stdafx.h"
#include "Enemy02.h"
#include "Game.h"
#include "GameData.h"
namespace {
	const int ATTACK_WAIT_TIME = 40;					//攻撃したときの待ち時間
	const float ATTACKED_WAIT_TIME = 20.0f;				//攻撃されたときの待ち時間
	const float SCALE_DIVISION_Z = 2.0f;				//スケールを割る数値
	const float PECHANKO_SCALE_Z = 10.0f;				//ぺちゃんこにするのに割る数値
	const float DEGREE_NUM = 80.0f;						//角度　単位：degree
	const float LENGTH = 50.0f;							//プレイヤーとの距離
	const int ATTACK_MINUS_PLAYER_HP = -1;				//攻撃時プレイヤーHPマイナス
	const float PLAYER_NOCKBACK_SPEED = 2500.0f;		//プレイヤーのノックバックスピード
	const int SCORE = 0;								//スコア
	const float JUMP_SPEED_DECAY = 0.85f;				//ジャンプ速度減衰
	const float PYON_SPEED = 2000.0f;					//ぴょんスピード
	const int STOP_TIMER = 120;							//往復タイマー　単位：秒
	const float MOVE_SPEED_X = 400.0f;					//X方向の移動速度
	const float JUMP_SPEED_ZERO_JUDGMENT = 200.0f;		//ジャンプ速度をゼロにする値
	const float DELTA_TIME = 1.0f / 60.0f;				//経過時間　単位：秒
	const float RIGHT_ANGLE = 90.0f;					//直角
	const float DEFAULT_GRAVITY = 200.0f;				//重力
	const float	DAMAGE_GRAVITY = 500.0f;				//重力
	const float SPRITE_W = 50.0f;			//スプライト幅
	const float SPRITE_H = 50.0f;			//スプライト高さ
}

Enemy02::Enemy02()
{
	//cmoファイルの読み込み。
	m_skinModel.Init(L"Assets/modelData/wingKuribo.cmo");
	m_fumuSE = g_goMgr.NewGameObject<CSoundSource>(0);
	m_fumuSE->Init(L"Assets/sound/fumu.wav");
	if (g_gameData.GetStageNo() != g_gameData.enStage_One) {
		//右か左スタートかランダム
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
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	if (m_player != nullptr
		&& m_game != nullptr
		&& !m_game->GetGameOverFlag()
		&& !m_game->GetStar()) {
		//プレイヤーに伸びるベクトル＆正規化
		VectorToPlayer();
		//角度を求める
		Angle();
		if (!m_isDeath) {
			//動く処理
			Move();
			//攻撃
			Attack();
		}
		//回転
		Rotation();
		//死亡*スコア値
		Death(SCORE);
		DeathEnemyBallContact(SCORE);
		DeathFireBall(SCORE);

	}
}

void Enemy02::Move()
{
	float GRAVITY = DEFAULT_GRAVITY;
	//攻撃されてないなら
	if (!m_isAttacked) {
		//ぴょんぴょん
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
		//往復
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
	//攻撃されたら
	else {
		m_moveSpeed = CVector3::Zero();
		GRAVITY = DAMAGE_GRAVITY;
	}
	//重力
	m_moveSpeed.y -= GRAVITY;

	m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);
}
void Enemy02::Rotation()
{
	//ｘとｚのベクトルから角度を求めて回転させる。
	auto moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));  //角度を求める関数
}
void Enemy02::Attack()
{
	if (!m_isAttacked) {
		if (!m_player->IsHipDrop()) {
			//攻撃中じゃなかったら攻撃
			if (m_isAttack == false) {
				if (fabs(m_angle) > CMath::DegToRad(DEGREE_NUM) && m_len < LENGTH) {
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
			else {
				m_waitTimer++;
				if (m_waitTimer == ATTACK_WAIT_TIME) {
					m_waitTimer = 0;
					m_isAttack = false;		//攻撃してない。
				}
			}
		}
	}
}

void Enemy02::Death(int score)
{
	if (!m_player->IsHipDrop()) {
		//攻撃されてなかったら
		if (m_isAttacked == false) {
			if (fabs(m_angle) <= CMath::DegToRad(DEGREE_NUM) && m_len < LENGTH) {
				m_scale.z /= SCALE_DIVISION_Z;
				m_player->SetJumpFlag(true);	//ジャンプさせる
				m_fumuSE->Play(false);
				m_isAttacked = true;		//攻撃された
			}
		}
		//攻撃されたら少し待ってから削除
		if (m_isAttacked == true) {
			m_waitTimer++;
			if (m_waitTimer == ATTACKED_WAIT_TIME) {
				m_game->SetScore(score);
				g_goMgr.DeleteGameObject(this);
			}
		}
	}
	else {
		//攻撃されてなかったら
		if (m_isAttacked == false) {
			if (fabs(m_angle) <= CMath::DegToRad(RIGHT_ANGLE) && m_len < LENGTH) {
				m_scale.z /= PECHANKO_SCALE_Z;
				m_fumuSE->Play(false);
				m_isAttacked = true;		//攻撃された
			}
		}
		//攻撃されたら少し待ってから削除
		if (m_isAttacked == true) {
			m_waitTimer++;
			if (m_waitTimer == ATTACKED_WAIT_TIME) {
				m_game->SetScore(score);
				g_goMgr.DeleteGameObject(this);
			}
		}
	}
}