#include "stdafx.h"
#include "Box.h"

const int INIT_TIME = 3;				//削除までの待ち時間

Box::Box()
{
	m_skinModel.Init(L"Assets/modelData/Boxmae.cmo");
	m_ghostObject.CreateBox(m_ghostPos, m_rotation, m_ghostScale);
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
	m_staticObject.SetPositionAndRotation(m_position, m_rotation);

	if (m_isContact) {
		m_timer++;
		if (m_timer == INIT_TIME) {
			if (!m_isInitModel) {
				m_skinModel.Init(L"Assets/modelData/Boxato.cmo");
				m_item = g_goMgr.NewGameObject<Item>("item");
				CVector3 itemPos = m_position;
				itemPos.y += 80.0f;
				m_item->SetPosition(itemPos);
				m_isInitModel = true;
			}
		}
	}
}
void Box::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal,
		1
	);
	m_skinModel.RimLightOff();
}