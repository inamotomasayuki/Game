#include "stdafx.h"
#include "EnemyFireBall.h"
#include "../Game.h"

namespace {
	const float DEGREE_NUM = 30.0f;						//角度　単位：degree
	const float LENGTH = 70.0f;							//プレイヤーとの距離
	const int ATTACK_MINUS_PLAYER_HP = -1;				//攻撃時プレイヤーHPマイナス
	const float PLAYER_NOCKBACK_SPEED = 2500.0f;		//プレイヤーのノックバックスピード
	const float MOVE_SPEED = 10.0f;						//ファイアボール移動速度
	const int DLETE_TIME = 300;							//削除時間
}

EnemyFireBall::EnemyFireBall()
{
	m_skinModel.Init(L"Assets/modelData/FireBall.cmo");
}


EnemyFireBall::~EnemyFireBall()
{
}

void EnemyFireBall::Update()
{
	m_player = g_goMgr.FindGameObject<Player>("player");
	if (m_player != nullptr) {
		m_position += m_vector * MOVE_SPEED;
		//攻撃
		Attack();
	}
	//削除処理
	Delete();
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

void EnemyFireBall::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//リムライトオフ
	m_skinModel.RimLightOff();
	//シャドウレシーバーオフ
	m_skinModel.ShadowReciverOff();
}

void EnemyFireBall::Attack()
{
	//距離を求める
	auto vec = m_player->GetPositon() - m_position;
	auto len = vec.Length();
	vec.Normalize();
	// 角度を求める
	auto naiseki = vec.Dot(CVector3::AxisY());
	auto angle = acos(naiseki);
	

	const auto& game = g_goMgr.FindGameObject<Game>("game");
	if (!m_isAttack) {
		if (len < LENGTH) {
			//あちちダメージ
			m_player->SetIsAchichi();
			m_player->SetAchichiVec(vec);
			m_isAttack = true;
			if (!m_player->GetisItem()) {
				game->SetHP(ATTACK_MINUS_PLAYER_HP);
			}
		}
	}
}

void EnemyFireBall::Delete()
{
	m_deleteTimer++;
	if (m_deleteTimer == DLETE_TIME) {
		g_goMgr.DeleteGameObject(this);
	}
	if (m_isAttack) {
		g_goMgr.DeleteGameObject(this);
	}
}