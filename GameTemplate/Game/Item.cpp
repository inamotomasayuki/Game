#include "stdafx.h"
#include "Item.h"
#include "Box.h"

const float DELTA_TIME = 1.0f / 60.0f;			//経過時間　単位：秒
const float GRAVITY = 10.0f;

Item::Item()
{
	m_skinModel.Init(L"Assets/modelData/mikan.cmo");
	m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
}


Item::~Item()
{
}

void Item::Update()
{
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_ghostObject.SetPosition(m_position);
	m_box = g_goMgr.FindGameObject<Box>("box");
	auto boxPos = m_box->GetPosition();
	auto posUp = boxPos.y + 80.0f;
	if (!m_box->GetIsHipDrop()) {
		if (posUp > m_position.y) {
			m_position.y += 2.0f;
		}
	}
	else {
		m_moveSpeed.y -= GRAVITY;	
		m_position = m_charaCon.Execute(DELTA_TIME, m_moveSpeed);
	}

	//削除
	if (m_isGet) {
		g_goMgr.DeleteGameObject(this);
	}
}

void Item::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	m_skinModel.RimLightOff();
	m_skinModel.SetDligColor(0, 30.0f);
	m_skinModel.SetDligColor(1, 30.0f);
}