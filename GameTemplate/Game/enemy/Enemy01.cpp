#include "stdafx.h"
#include "Enemy01.h"
#include "Game.h"

namespace {
	const float LENGTH_UPPER = 900.0f;				//追跡上限距離
	const float LENGTH_UNDER = 50.0f;				//追跡下限距離
	const float MOVE_SPEED = 400.0f;				//移動速度
	const float MINIMUM = 0.0001f;					//極小
	const float DELTA_TIME = 1.0f / 60.0f;			//経過時間　単位：秒
	const float MOVE_STOP = 0.01f;					//止まる
	const float INIT_POS_LEN = 10.0f;				//リターン時の初期位置との距離
	const int ATTACK_WAIT_TIME = 40;				//攻撃したときの待ち時間
	const float ATTACKED_WAIT_TIME = 20.0f;			//攻撃されたときの待ち時間
	const float SCALE_DIVISION_Z = 2.0f;			//スケールを割る数値
	const float PECHANKO_SCALE_Z = 10.0f;			//ぺちゃんこにするのに割る数値
	const float DEGREE_NUM = 80.0f;					//角度　単位：degree
	const float RIGHT_ANGLE = 100.0f;				//直角
	const float LENGTH = 50.0f;						//プレイヤーとの距離
	const int ATTACK_MINUS_PLAYER_HP = -1;			//攻撃時プレイヤーHPマイナス
	const float PLAYER_NOCKBACK_SPEED = 2500.0f;	//プレイヤーのノックバックスピード
	const int SCORE = 0;					//スコア
	const float SPRITE_W = 50.0f;			//スプライト幅
	const float SPRITE_H = 50.0f;			//スプライト高さ
}

Enemy01::Enemy01()
{
	//cmoファイルの読み込み。
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
		auto warp = g_goMgr.FindGameObject<Warp>("warp");
		if (!m_isDeath) {
			if (!warp->IsWarp()) {
				//追跡
				Search();
				//攻撃（プレイヤーをノックバック）
				Attack();
			}
			else {
				m_moveSpeed = m_v * MOVE_STOP;
			}
			//元の位置に戻る
			Return();
		}
		m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);

		//回転
		Rotation();
		//死亡
		Death(SCORE);
		DeathEnemyBallContact(SCORE);
		DeathFireBall(SCORE);
	}
}
void Enemy01::Search()
{
	//攻撃していないかつ攻撃を受けていない
	if (m_isAttack == false
		&& m_isAttacked == false) {
		//下記の距離の範囲ならかつプレイヤーが攻撃を受けていなかったら
		if (m_len > LENGTH_UNDER
			&& m_len < LENGTH_UPPER
			&& m_player->GetIsAttacked() == false) {
			//プレイヤーを追跡
			m_moveSpeed = m_v * MOVE_SPEED;
			m_moveSpeed.y = 0.0f;
		}
		else {
			//追跡しない。
			//回転させるために０ではない。
			m_moveSpeed = m_v * MINIMUM;
		}
	}
}
void Enemy01::Return()
{
	//下記の距離の範囲なら
	if (m_len > LENGTH_UPPER) {
		auto initPos = m_initialPos - m_position;
		auto len = initPos.Length();
		initPos.Normalize();
		if (len < INIT_POS_LEN) {
			//戻ったら動かない
			m_moveSpeed = CVector3::Zero();
		}
		else {
			//元の位置に戻る
			m_moveSpeed = initPos * MOVE_SPEED;
		}
	}
}
void Enemy01::Rotation()
{
	//ｘとｚのベクトルから角度を求めて回転させる。
	auto moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));  //角度を求める関数
}
void Enemy01::Attack()
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

void Enemy01::Death(int score)
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