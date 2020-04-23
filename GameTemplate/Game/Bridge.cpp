#include "stdafx.h"
#include "Bridge.h"

Bridge::Bridge()
{
	m_skinModel.Init(L"Assets/modelData/bridge.cmo");
}


Bridge::~Bridge()
{
}

void Bridge::Update()
{
	g_goMgr.FindGameObjects<Button>("button", [&](Button* button)->bool {
		if (button->GetState() == button->enState_0) {
			if (!m_isCreatePhysics) {
				m_physicsStaticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
				m_isCreatePhysics = true;
			}
		}
		else {
			if (m_isCreatePhysics) {
				m_physicsStaticObject.Delete();
				m_isCreatePhysics = false;
			}
		}
		return true;
		});
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Bridge::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	m_skinModel.RimLightOff();
	g_goMgr.FindGameObjects<Button>("button", [&](Button* button)->bool {
		if(button->GetState() == button->enState_0){
			m_skinModel.DitheringOff();
		}
		else{
			m_skinModel.DitheringOn();
		}
		return true;
	});
}