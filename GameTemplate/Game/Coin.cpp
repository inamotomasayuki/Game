#include "stdafx.h"
#include "Coin.h"
#include "Game.h"

const float PYON_UP = 20.0f;
const float PYON_DOWN = -20.0f;
const int PYON_UP_TIME = 5;
const int PYON_DOWN_TIME = 8;
const int DELETE_TIME = 10;
const int COIN_SCORE = 1;
const float FLAG_LENGTH = 40.0f;
const float ROTATION_SPEED = 5.0f;
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
	float rotSpeed = 0.0f;;
	rotSpeed += ROTATION_SPEED;
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
	m_rotation.Multiply(addRot);
}

void Coin::GetCoin()
{
	if (m_player != nullptr) {
		CVector3 v = m_player->GetPositon() - m_position;
		float len = v.Length();
		//距離が一定以下なら取得フラグを立てる
		if (len < FLAG_LENGTH) {
			m_coinGetFlag = true;
		}
	}
	//フラグが立ったら跳ねさせて取得する
	if (m_coinGetFlag == true) {
		m_timer++;
		if (m_timer < PYON_UP_TIME) {
			m_moveSpeed.y = PYON_UP;
			m_position += m_moveSpeed;
		}
		if (m_timer >= PYON_UP_TIME && m_timer < PYON_DOWN_TIME) {
			m_moveSpeed.y = PYON_DOWN;
			m_position += m_moveSpeed;
		}
		if (m_timer == DELETE_TIME) {
			m_timer = 0;
			m_game->SetScore(COIN_SCORE);
			g_goMgr.DeleteGameObject(this);
		}
	}
}