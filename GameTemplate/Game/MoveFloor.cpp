#include "stdafx.h"
#include "MoveFloor.h"
#include "Player.h"

const float MOVE_X_SPEED = 1000.0f;		//X方向の移動速度
const float RETURN_TIME = 220.0f;		//ステート切り替えし時間
const float STOP_TIME = 170.0f;			//止まる時間
const float ZERO = 0.0f;				//ゼロ

MoveFloor::MoveFloor()
{
	m_skinModel.Init(L"Assets/modelData/moveFloor.cmo");
	m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
	m_staticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
	m_state = enState_right;
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
	m_staticObject.SetPositionAndRotation(m_position, m_rotation);
}
void MoveFloor::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	m_skinModel.RimLightOff();
}
void MoveFloor::RoundTrip()
{
	m_timer++;
	//往復
	if (m_state == enState_right) {
		if (m_timer == RETURN_TIME) {
			m_moveSpeed.x += MOVE_X_SPEED;
			m_timer = ZERO;
			m_state = enState_left;
		}
		else if (m_timer == STOP_TIME) {
			m_moveSpeed.x = ZERO;
		}
	}
	if (m_state == enState_left) {
		if (m_timer == RETURN_TIME) {
			m_moveSpeed.x -= MOVE_X_SPEED;
			m_timer = ZERO;
			m_state = enState_right;
		}
		else if (m_timer == STOP_TIME) {
			m_moveSpeed.x = ZERO;
		}
	}


	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
	m_player = g_goMgr.FindGameObject<Player>("player");
	if (m_player != nullptr) {
		//プレイヤーに速度を渡す
		m_player->SetFloorSpeed(m_moveSpeed);
	}
}