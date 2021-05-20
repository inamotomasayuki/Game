#include "stdafx.h"
#include "FireBall.h"
#include "Player.h"

namespace {
	const float CHARACON_RADIUS = 5.0f;					//キャラコンの半径
	const float CHARACON_HIGHT = 5.0f;					//キャラコンの高さ
	const float DELTA_TIME = 1.0f / 60.0f;				//経過時間　単位：秒
	const float FIREBALL_GRAVITY = 1500.0f;				//重力
	const float JUMP_SPEED_DECAY = 0.85f;				//ジャンプ速度減衰
	const float PYON_SPEED = 800.0f;					//ぴょんスピード
	const float JUMP_SPEED_ZERO_JUDGMENT = 200.0f;		//ジャンプ速度をゼロにする値
	const float SPEED = 2000.0f;						//速度
	const CVector3 TARGET = { 0.0f, 100.0f, 0.0f };		//ターゲット
	const CVector3 POS = { 0.0f, 100.0f, 30.0f };		//位置
	const CVector3 POS_RUN = { 0.0f, 100.0f, 40.0f };	//位置
	const float DELETE_TIME = 300;						//削除時間
}
FireBall::FireBall()
{
	m_skinModel.Init(L"Assets/modelData/FireBall.cmo");
	//ファイアボールを生成する座標を求める
	{
		m_player = g_goMgr.FindGameObject<Player>("player");
		m_rotation = m_player->GetRotation();
		m_targetPos = m_player->GetPositon();
		m_targetPos.y += 10.0f;
		if (g_pad[0].IsPress(enButtonB)) {
			m_position = POS_RUN;
		}
		else {
			m_position = POS;
		}
		m_toPos = m_position - TARGET;
		m_rotation.Multiply(m_toPos);
		m_position = m_targetPos + m_toPos;
		m_vectorXZ = m_position - m_player->GetPositon();
		m_vectorXZ.y = 0.0f;
		m_vectorXZ.Normalize();
		m_vectorXZ *= SPEED;
	}
	//キャラクターコントローラー初期化
	m_charaCon.Init(
		CHARACON_RADIUS,			//半径
		CHARACON_HIGHT,				//高さ
		m_position					//初期座標
	);

}


FireBall::~FireBall()
{
}

void FireBall::Update()
{
	m_deleteTimer++;
	//一定時間で削除
	if (m_deleteTimer == DELETE_TIME) {
		g_goMgr.DeleteGameObject(this);
	}
	//スピード
	m_moveSpeed = m_vectorXZ;
	//跳ね返り
	if (m_charaCon.IsWallHit()) {
		m_moveSpeed = m_charaCon.GetReturnVector() * SPEED;
	}
	m_moveSpeed.y -= FIREBALL_GRAVITY;
	//ぴょんぴょん
	if (m_charaCon.IsOnGround()) {
		m_jumpSpeed = PYON_SPEED;
		m_isJump = true;
	}
	if (m_isJump == true) {
		m_moveSpeed.y = m_jumpSpeed;
		m_jumpSpeed *= JUMP_SPEED_DECAY;
		if (m_jumpSpeed < JUMP_SPEED_ZERO_JUDGMENT) {
			m_jumpSpeed = 0;
			m_isJump = false;
		}
	}
	m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void FireBall::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
}