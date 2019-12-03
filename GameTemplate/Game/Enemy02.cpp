#include "stdafx.h"
#include "Enemy02.h"
#include "Game.h"

Enemy02::Enemy02()
{
	//cmoファイルの読み込み。
	m_skinModel.Init(L"Assets/modelData/kuribo.cmo");
	m_state = enState_right;
}

void Enemy02::Update()
{
	m_player = g_goMgr.FindGameObject<Player>("player");
	m_game = g_goMgr.FindGameObject<Game>("game");
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	if (m_player != nullptr) {
		//プレイヤーに伸びるベクトル＆正規化
		VectorToPlayer();
		//角度を求める
		Angle();
		//動く処理
		Move();
		//攻撃
		Attack();
		Rotation();
		//死亡*スコア値
		Death(10);
	}
}

void Enemy02::Move()
{
	float GRAVITY = 200.0f;
	//攻撃されてないなら
	if (!m_isAttacked) {
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
		if (m_state == enState_right) {
			m_moveSpeed.x = 400.0f;
			if (m_timer == 120) {
				m_timer = 0;
				m_state = enState_left;
			}
		}
		if (m_state == enState_left) {
			m_moveSpeed.x = -400.0f;
			if (m_timer == 120) {
				m_timer = 0;
				m_state = enState_right;
			}
		}
	}
	//攻撃されたら
	else {
		m_moveSpeed = CVector3::Zero();
		GRAVITY = 500.0f;
	}
	//重力
	m_moveSpeed.y -= GRAVITY;

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