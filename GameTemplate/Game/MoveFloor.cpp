#include "stdafx.h"
#include "MoveFloor.h"
#include "Player.h"

MoveFloor::MoveFloor()
{
	m_skinModel.Init(L"Assets/modelData/moveFloor.cmo");
	m_state = enState_left;
	m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
}


MoveFloor::~MoveFloor()
{
}
void MoveFloor::Update()
{		

	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//往復
	RoundTrip();
	m_ghostObject.SetPosition(m_position);
}
void MoveFloor::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
	);
}
void MoveFloor::RoundTrip()
{
	m_timer++;
	//左
	if (m_state == enState_left) {
		if (m_timer == 120) {
			m_moveSpeed.x = 300.0f;
			m_timer = 0;
			m_state = enState_right;
		}
		else if (m_timer == 90.0f) {
			m_moveSpeed.x = 0;
		}
	}
	//右
	if (m_state == enState_right) {
		if (m_timer == 120) {
			m_moveSpeed.x = -300.0f;
			m_timer = 0;
			m_state = enState_left;
		}
		else if (m_timer == 90.0f) {
			m_moveSpeed.x = 0;
		}
	}
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
	m_player = g_goMgr.FindGameObject<Player>("player");
	m_player->SetFloorSpeed(m_moveSpeed);
}