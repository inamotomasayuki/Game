#include "stdafx.h"
#include "Enemy04.h"
#include "Game.h"
#include "EnemyFireBall.h"

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
	const float RIGHT_ANGLE = 90.0f;					//直角
	const float FIRE_GENERATE_LENGTH_MAX = 600.0f;		//ファイアー生成距離上限
	const float FIRE_GENERATE_LENGTH_MIN = 150.0f;		//ファイアー生成距離下限
	const int FIRE_GENERATE_INTERVAL = 70;				//ファイアー先生間隔
	const float FIRE_GENERATE_POS_Y = 50.0f;			//ファイアー生成Y位置
	const float FIRE_GENERATE_ANGLE = 40.0f;			//ファイアー生成角度

	const float VIEW_BOLUME_WIDTH = 1280.0f;		//ビューボリュームの幅
	const float VIEW_BOLUME_HIGHT = 720.0f;			//ビューボリュームの高さ
	const float F_NEAR = 0.1f;						//近平面
	const float F_FAR = 100.0f;						//遠平面
	const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//カメラの位置
	const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//カメラの注視点
	const CVector3 CAMERA_UP = { 0,1,0 };				//カメラの上方向

	const float SPRITE_W = 50.0f;			//スプライト幅
	const float SPRITE_H = 50.0f;			//スプライト高さ

}

Enemy04::Enemy04()
{
	//cmoファイルの読み込み。
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
			//攻撃
			Attack();
		}
		//ファイアボール生成
		FireBallGenerate();
		//回転
		Rotation();
		//死亡*スコア値
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
		//ｘとｚのベクトルから角度を求めて回転させる。
		auto moveSpeedXZ = m_player->GetPositon() - m_position;
		moveSpeedXZ.y = 0.0f;
		moveSpeedXZ.Normalize();
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));  //角度を求める関数
	}
}
void Enemy04::Attack()
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
					m_player->SetIsAttacked(false);		//攻撃されてない。
				}
			}
		}
	}
}

void Enemy04::Death(int score)
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
				//プレイヤーへの向きを求める
				auto vecToPlayer = m_player->GetPositon() - m_position;
				vecToPlayer.Normalize();
				auto pos = m_position;
				pos.y += FIRE_GENERATE_POS_Y;			//少し上げる
				//生成
				const auto& fireBall = g_goMgr.NewGameObject<EnemyFireBall>("enemyFireBall");
				fireBall->SetPosition(pos);
				fireBall->SetVector(vecToPlayer);
				m_fireSE->Play(false);
			}
			//生成間隔
			m_fireGenerateTimer++;
			if (m_fireGenerateTimer >= FIRE_GENERATE_INTERVAL) {
				m_fireGenerateTimer = 0;
			}
		}
	}
}