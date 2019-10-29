#include "stdafx.h"
#include "JumpFloor.h"


JumpFloor::JumpFloor()
{
	m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
}


JumpFloor::~JumpFloor()
{
}

void JumpFloor::Update()
{
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_ghostObject.SetPosition(m_position);
}
void JumpFloor::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
	);
}