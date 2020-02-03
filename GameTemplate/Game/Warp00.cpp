#include "stdafx.h"
#include "Warp00.h"

const float ROTATION_SPEED = 2.0f;				//回転速度
const float LENGTH_NEAR = 50.0f;				//近い	
const float LENGTH_LEAVE = 100.0f;				//離れた
Warp00::Warp00()
{
	m_skinModel.Init(L"Assets/modelData/warp.cmo");
}


Warp00::~Warp00()
{
}

void Warp00::Update()
{
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//回転
	Rotation();
	m_player = g_goMgr.FindGameObject<Player>("player");
	if (m_player != nullptr) {
		auto v = m_position - m_player->GetPositon();
		auto len = v.Length();
		if (len < LENGTH_NEAR
			&& !m_player->GetIsLeave00()) {
			m_player->SetIsWarp00(true);
		}
		if (len >= LENGTH_LEAVE) {
			m_player->SetIsLeave00(false);
		}
	}

}
void Warp00::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	m_skinModel.RimLightOff();
}
void Warp00::Rotation()
{
	//一定速度で回転させる
	float rotSpeed = 0.0f;;
	rotSpeed += ROTATION_SPEED;
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
	m_rotation.Multiply(addRot);

}