#include "stdafx.h"
#include "Star.h"
#include "Player.h"
#include "Game.h"

const int CLEAR_TIME = 25;				//クリアまでの時間
const float ROTATION_SPEED = 5.0f;					//回転速度
const float GET_STAR_POSITION_Y = 100.0f;			//星取った時のYの位置

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
		if (m_game->GetStar()) {
			m_timer++;
			auto pos = m_player->GetPositon();
			pos.y += GET_STAR_POSITION_Y;
			m_position = pos;
			if (m_timer == CLEAR_TIME) {
				m_getStar = true;
			}
		}
	}
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
