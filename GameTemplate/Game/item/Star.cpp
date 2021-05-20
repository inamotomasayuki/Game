#include "stdafx.h"
#include "Star.h"
#include "../player/Player.h"
#include "Game.h"

namespace {
	const int CLEAR_TIME = 25;							//クリアまでの時間
	const float ROTATION_SPEED = 5.0f;					//回転速度
	const float GET_STAR_POSITION_Y = 100.0f;			//星取った時のYの位置
	const float DLIG_COLOR = 1.8f;						//ディレクションライトの明るさ	
	const float POS_Y = 150.0f;							//星の高さ
}
Star::Star()
{
	m_skinModel.Init(L"Assets/modelData/star.cmo");
	m_ghost.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
}


Star::~Star()
{
}

void Star::Update()
{
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//回転
	Rotation();
	m_player = g_goMgr.FindGameObject<Player>("player");
	m_game = g_goMgr.FindGameObject<Game>("game");
	if (m_player != nullptr
		&& m_game != nullptr) {
		//星を取ったらプレイヤーの頭上へ
		if (m_game->GetStar()) {
			m_timer++;
			auto pos = m_player->GetPositon();
			if (m_player->GetisItem()) {
				//通常時
				pos.y += POS_Y;
			}
			else {
				//アイテムで大きくなってる時
				pos.y += GET_STAR_POSITION_Y;
			}
			m_position = pos;
			if (m_timer == CLEAR_TIME) {
				m_getStar = true;
			}
		}
	}
	//ゴースト更新
	m_ghost.SetPosition(m_position);
	m_ghost.SetRotation(m_rotation);
}

void Star::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//リムライトオフ
	m_skinModel.RimLightOff();
	m_skinModel.ToonOff();
	m_skinModel.ShadowReciverOff();
	//ライトの方向・明るさ
	m_skinModel.SetDligColor(0, DLIG_COLOR);
	m_skinModel.SetDligColor(1, DLIG_COLOR);
}

void Star::Rotation()
{
	//一定速度で回転させる
	float rotSpeed = 0.0f;;
	rotSpeed += ROTATION_SPEED;
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
	m_rotation.Multiply(addRot);
}
