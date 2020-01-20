#include "stdafx.h"
#include "Box.h"

Box::Box()
{
	m_skinModel.Init(L"Assets/modelData/Boxmae.cmo");
	m_ghostObject.CreateBox(m_ghostPos, m_rotation, m_ghostScale);
	m_ghostMesh.CreateMesh(m_ghostMeshPos, m_rotation, m_ghostScale, m_skinModel);
	m_staticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
}


Box::~Box()
{
}
void Box::Update()
{
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_ghostObject.SetPosition(m_ghostPos);
	m_ghostMesh.SetPosition(m_ghostMeshPos);
	m_staticObject.SetPositionAndRotation(m_position, m_rotation);

	if (m_isContact) {
		if (!m_isInitModel) {
			m_skinModel.Init(L"Assets/modelData/Boxato.cmo");
			m_item = g_goMgr.NewGameObject<Item>("item");
			CVector3 itemPos = m_position;
			itemPos.y -= 100.0f;
			if (!m_isHipDrop) {
				m_item->SetPosition(m_position);
			}
			else {
				m_item->SetPosition(itemPos);
			}
			m_isInitModel = true;
		}
	}
}
void Box::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	m_skinModel.RimLightOff();
}