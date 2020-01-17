#include "stdafx.h"
#include "Item.h"


Item::Item()
{
	m_skinModel.Init(L"Assets/modelData/mikan.cmo");
	m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
	//m_staticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
}


Item::~Item()
{
}

void Item::Update()
{
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_ghostObject.SetPosition(m_position);
	//m_staticObject.SetPositionAndRotation(m_position, m_rotation);
}

void Item::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal,
		1
	);
	m_skinModel.RimLightOff();
}