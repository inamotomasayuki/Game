#include "stdafx.h"
#include "MoveFloor.h"
#include "../player/Player.h"
#include "GameData.h"

namespace {
	const float MOVE_X_SPEED = 1000.0f;		//X方向の移動速度
	const float RETURN_TIME = 220.0f;		//ステート切り替えし時間
	const float STOP_TIME = 170.0f;			//止まる時間
	const int ZERO = 0;						//ゼロ
	const float DELTA_TIME = 1.0f / 60.0f;	//経過時間　単位：秒
}

MoveFloor::MoveFloor()
{
}


MoveFloor::~MoveFloor()
{
}
void MoveFloor::Update()
{
	if (!m_isInit) {
		Init();
		m_isInit = true;
	}
	//往復
	RoundTrip();
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_ghostObject.SetPosition(m_position);
	m_staticObject.SetPositionAndRotation(m_position, m_rotation);
}
void MoveFloor::Draw()
{
	if (m_isInit) {
		m_skinModel.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			enRenderMode_Normal
		);
		//リムライトオフ
		m_skinModel.RimLightOff();
		//トゥーンオフ
		m_skinModel.ToonOff();
	}
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
	m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);
	const auto& player = g_goMgr.FindGameObject<Player>("player");
	if (player != nullptr) {
		//プレイヤーに速度を渡す
		player->SetFloorSpeed(m_moveSpeed);
	}
}

void MoveFloor::Init()
{
	m_skinModel.Init(L"Assets/modelData/moveFloor.cmo");
	m_skinModel.LoadNormalMap(L"Assets/modelData/Stone_floor_n.dds");
	m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
	m_staticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
	//モデルの都合上変換
	auto y = m_scale.z;
	m_scale.z = m_scale.y;
	m_scale.y = y;
	if (g_gameData.GetStageNo() == g_gameData.enStage_One) {
		//ステージ１でのステート
		m_state = enState_left;
	}
}