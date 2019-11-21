#include "stdafx.h"
#include "Enemy02.h"
#include "Game.h"

Enemy02::Enemy02()
{
	//cmoファイルの読み込み。
	m_skinModel.Init(L"Assets/modelData/kuribo.cmo");
}

void Enemy02::Update()
{
	m_player = g_goMgr.FindGameObject<Player>("player");
	m_game = g_goMgr.FindGameObject<Game>("game");
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//プレイヤーに伸びるベクトル＆正規化
	VectorToPlayer();
	//角度を求める
	Angle();
	//動く処理
	Move();
	//攻撃
	Attack();
	//死亡*スコア値
	Death(10);
}

void Enemy02::Move()
{
	//ぴょんぴょん
	if (m_charaCon.IsOnGround()) {
		m_jumpSpeed = 2000.0f;
		m_isJump = true;
	}
	if (m_isJump == true) {
		m_moveSpeed.y = m_jumpSpeed;
		m_jumpSpeed *= 0.85f;
		if (m_jumpSpeed < 200.0f) {
			m_jumpSpeed = 0;
			m_isJump = false;
		}
	}
	m_timer++;
	m_moveSpeed.x += m_speed;
	if (m_timer == 120) {
		m_speed *= -1.0f;
		m_timer = 0;

	}
	else if (m_timer >= 80.0f) {
		m_moveSpeed.x *= 0.97f;
		if (m_moveSpeed.Length() < 0.1f) {
			m_moveSpeed.x = 0;
		}
	}

	m_moveSpeed.y -= 200.0f;
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
}
void Enemy02::Rotation()
{
	//ｘとｚのベクトルから角度を求めて回転させる。
	auto moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(moveSpeedXZ.x, moveSpeedXZ.z));  //角度を求める関数
}