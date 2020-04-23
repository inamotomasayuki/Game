#include "stdafx.h"
#include "Wall.h"

Wall::Wall()
{
	m_skinModel.Init(L"Assets/modelData/wall.cmo");
	m_physicsStaticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
}


Wall::~Wall()
{
}

void Wall::Update()
{
	g_goMgr.FindGameObjects<Button>("button1", [&](Button* button)->bool {
		if (button->GetState() == button->enState_1) {
			if (m_skinModel.GetDitheringPow() == 0) {
				g_goMgr.DeleteGameObject(this);
			}
		}
		return true;
	});

	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);
}

void Wall::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	m_skinModel.RimLightOff();
	g_goMgr.FindGameObjects<Button>("button1", [&](Button* button)->bool {
		if (button->GetState() == button->enState_1) {
			m_skinModel.DitheringOn();
			m_skinModel.DecDitheringPow();
		}
		return true;
	});
}