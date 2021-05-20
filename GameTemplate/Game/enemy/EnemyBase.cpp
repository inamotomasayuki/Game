#include "stdafx.h"
#include "EnemyBase.h"
#include "Game.h"
#include "EnemyBall.h"

namespace {
	const float LENGTH = 75.0f;					//玉との距離
	const float PYON_UP = 500.0f;				//跳ね上がるときの速度
	const float PYON_DOWN = -500.0f;			//跳ね落ちるときの速度
	const int PYON_UP_TIME = 6;					//跳ね上がる時間
	const int PYON_DOWN_TIME = 9;				//跳ね落ちる時間
	const int DELETE_TIME = 11;					//削除までの待ち時間
	const int SCORE = 0;						//スコア
	const float DELTA_TIME = 1.0f / 60.0f;		//経過時間　単位：秒
	//スプライト
	const float SPRITE_ROT_SPEED = 6.0f;		//スプライト回転
	const float SPRITE_AUTO_ROT_SPEED = 10.0f;	//スプライト自動回転
	const float FAR_LENGTH = 3000.0f;			//遠い
	const float FAR_SCALE = 0.0004f;			//遠いとき拡大率
	const float NEAR_LENGTH = 1000.0f;			//近い
	const float NEAR_SCALE = 0.001f;			//近いとき拡大率
	const float SPRITE_POS_Y = 100.0f;			//スプライトY位置
	const float POS_Y = 0.01f;
}

void EnemyBase::Draw()
{
	//シルエット
	if (g_pad[0].IsTrigger(enButtonX)) {
		if (!m_isDisplay) {
			m_isDisplay = true;
		}
		else {
			m_isDisplay = false;
		}
	}
	if (m_isDisplay) {
		m_skinModel.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			enRenderMode_Silhouette
		);
	}
	//描画
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//リムライトオフ
	m_skinModel.RimLightOff();
	//シャドウレシーバーオフ
	//m_skinModel.ShadowReciverOff();
	m_skinModel.ToonOff();
}

void EnemyBase::Draw2D()
{
	m_rotSpeed += g_pad[0].GetRStickXF() * SPRITE_ROT_SPEED;
	m_backRotSpeed += g_pad[0].GetRStickXF() * SPRITE_ROT_SPEED;
	m_rotSpeed += SPRITE_AUTO_ROT_SPEED;
	m_backRotSpeed += SPRITE_AUTO_ROT_SPEED;
	if (m_game != nullptr) {
		if (!m_game->GetGameOverFlag()) {
			if (m_isDisplay) {
				m_spriteRot.SetRotationDeg(CVector3::AxisY(), m_rotSpeed);
				m_spriteBackRot.SetRotationDeg(CVector3::AxisY(), m_backRotSpeed);
				auto pos = m_position;
				pos.y += SPRITE_POS_Y;
				auto scale = m_scale;
				if (m_len >= FAR_LENGTH) {
					scale *= m_len * FAR_SCALE;
					pos.y += m_len * POS_Y;
				}
				auto vec = g_camera3D.GetPosition() - pos;
				auto toCameraLen = vec.Length();
				if (toCameraLen <= NEAR_LENGTH) {
					scale *= toCameraLen * NEAR_SCALE;
				}
				m_sprite.UpdateWorldMatrix(pos, m_spriteRot, scale);
				m_spriteBack.UpdateWorldMatrix(pos, m_spriteBackRot, scale);
				//描画
				m_sprite.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
				m_spriteBack.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
			}
		}
	}
}

void EnemyBase::DeathEnemyBallContact(int score)
{

	g_goMgr.FindGameObjects<EnemyBall>("enemyBall", [this](EnemyBall* enemyBall)->bool {
		const auto& vector = enemyBall->GetPositon() - m_position;
		auto len = vector.Length();
		if (len < LENGTH 
			&& enemyBall->GetIsKicked() == true) {
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
			m_fumuSE->Play(false);
			m_game->SetScore(score);
			g_goMgr.DeleteGameObject(this);
		}
	}
}

void EnemyBase::DeathFireBall(int score)
{
	g_goMgr.FindGameObjects<FireBall>("fireBall", [this](FireBall* fireBall)->bool {
		const auto& vector = fireBall->GetPosition() - m_position;
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
			m_fumuSE->Play(false);
			m_game->SetScore(score);
			g_goMgr.DeleteGameObject(this);
		}
	}
}