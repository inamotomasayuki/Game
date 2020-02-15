#include "stdafx.h"
#include "EnemyBase.h"
#include "Game.h"
#include "EnemyBall.h"

const float LENGTH = 75.0f;					//玉との距離
const float PYON_UP = 500.0f;				//跳ね上がるときの速度
const float PYON_DOWN = -500.0f;			//跳ね落ちるときの速度
const int PYON_UP_TIME = 6;					//跳ね上がる時間
const int PYON_DOWN_TIME = 9;				//跳ね落ちる時間
const int DELETE_TIME = 11;					//削除までの待ち時間
const int SCORE = 1;						//スコア
const float DELTA_TIME = 1.0f / 60.0f;		//経過時間　単位：秒

void EnemyBase::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	m_skinModel.RimLightOff();
}

void EnemyBase::DeathEnemyBallContact(int score)
{

	g_goMgr.FindGameObjects<EnemyBall>("enemyBall", [this](EnemyBall* enemyBall)->bool {
		auto vector = enemyBall->GetPositon() - m_position;
		auto len = vector.Length();
		if (len < LENGTH) {
			m_charaCon.RemoveRigidBoby();
			m_isDeath = true;
		}
		return true;
		});

	//フラグが立ったら跳ねさせる
	if (m_isDeath) {
		m_timer++;
		if (m_timer < PYON_UP_TIME) {
			m_moveSpeed.y = PYON_UP;
		}
		if (m_timer >= PYON_UP_TIME && m_timer < PYON_DOWN_TIME) {
			m_moveSpeed.y = PYON_DOWN;
		}
		//削除
		if (m_timer == DELETE_TIME) {
			m_timer = 0;
			m_fumuSE.Play(false);
			m_game->SetScore(score);
			g_goMgr.DeleteGameObject(this);
		}
	}
}

void EnemyBase::DeathFireBall(int score)
{
	g_goMgr.FindGameObjects<FireBall>("fireBall", [this](FireBall* fireBall)->bool {
		auto vector = fireBall->GetPosition() - m_position;
		auto len = vector.Length();
		if (len < LENGTH) {
			m_charaCon.RemoveRigidBoby();
			m_isDeath = true;
		}
		return true;
		});

	//フラグが立ったら跳ねさせる
	if (m_isDeath) {
		m_timer++;
		if (m_timer < PYON_UP_TIME) {
			m_moveSpeed.y = PYON_UP;
		}
		if (m_timer >= PYON_UP_TIME && m_timer < PYON_DOWN_TIME) {
			m_moveSpeed.y = PYON_DOWN;
		}
		//削除
		if (m_timer == DELETE_TIME) {
			m_timer = 0;
			m_fumuSE.Play(false);
			m_game->SetScore(score);
			g_goMgr.DeleteGameObject(this);
		}
	}
}