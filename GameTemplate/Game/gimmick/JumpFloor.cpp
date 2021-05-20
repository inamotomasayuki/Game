#include "stdafx.h"
#include "JumpFloor.h"


JumpFloor::JumpFloor()
{
	m_skinModel.Init(L"Assets/modelData/jumpFloor.cmo");
	m_staticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
	m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
}


JumpFloor::~JumpFloor()
{
}

void JumpFloor::Update()
{
	m_staticObject.SetPositionAndRotation(m_position, m_rotation);
	m_ghostObject.SetPosition(m_position);
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}
void JumpFloor::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//リムライトオフ
	m_skinModel.RimLightOff();
}