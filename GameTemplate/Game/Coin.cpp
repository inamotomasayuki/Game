#include "stdafx.h"
#include "Coin.h"
#include "Game.h"

Coin::Coin()
{
	m_skinModel.Init(L"Assets/modelData/coin.cmo");
}


Coin::~Coin()
{

}

void Coin::Update()
{
	m_player = g_goMgr.FindGameObject<Player>("player");
	m_game = g_goMgr.FindGameObject<Game>("game");

	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//回転
	Rotation();
	//コイン取得処理
	GetCoin();
}
void Coin::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
}
void Coin::Rotation()
{
	//一定速度で回転させる
	float angle = 0.0f;;
	angle += 5.0f;
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), angle);
	m_rotation.Multiply(addRot);
}

void Coin::GetCoin()
{
	CVector3 v = m_player->GetPositon() - m_position;
	float len = v.Length();
	//距離が一定以下なら取得フラグを立てる
	if (len < 40.0f) {
		m_coinGetFlag = true;
	}
	//フラグが立ったら跳ねさせて取得する
	if (m_coinGetFlag == true) {
		m_timer++;
		if (m_timer < 5) {
			m_moveSpeed.y = 20.0f;
			m_position += m_moveSpeed;
		}
		if (m_timer >= 5 && m_timer < 8) {
			m_moveSpeed.y = -20.0f;
			m_position += m_moveSpeed;
		}
		if (m_timer == 10) {
			m_game->SetScore(10);
			m_timer = 0;
			m_game->SetScore(1);
			g_goMgr.DeleteGameObject(this);
		}
	}
}