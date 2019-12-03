#include "stdafx.h"
#include "EnemyBase.h"
#include "Game.h"

const float ATTACK_WAIT_TIME = 40.0f;		//攻撃したときの待ち時間
const float ATTACKED_WAIT_TIME = 20.0f;		//攻撃されたときの待ち時間
const float SCALE_DIVISION = 2.0f;		//スケールを割る数値
const float DEGREE_NUM = 80.0f;			//角度　単位：degree
const float LENGTH = 50.0f;				//プレイヤーとの距離

void EnemyBase::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
}
void EnemyBase::Attack()
{
	//攻撃中じゃなかったら攻撃
	if (m_isAttack == false) {
		if (fabs(m_angle) > CMath::DegToRad(DEGREE_NUM) && m_len < LENGTH) {
			m_v.y = 0.0f;
			//ノックバックさせる速度
			m_player->SetAddSpeed(m_v * 2500.0f);
			m_player->SetIsAttacked(true);	//攻撃された。
			m_isAttack = true;	//攻撃した。	
			m_game->SetHP(-1);
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

void EnemyBase::Death(int score)
{
	//攻撃されてなかったら
	if (m_isAttacked == false) {
		if (fabs(m_angle) <= CMath::DegToRad(80) && m_len < LENGTH) {
			m_scale.z /= SCALE_DIVISION;
			m_player->SetJumpFlag(true);	//ジャンプさせる
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