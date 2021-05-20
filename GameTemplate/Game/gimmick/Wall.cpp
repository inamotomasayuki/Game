#include "stdafx.h"
#include "Wall.h"

Wall::Wall()
{
}


Wall::~Wall()
{
}

void Wall::Update()
{
	//初期化
	if (!m_isInit) {
		Init();
		m_isInit = true;
	}
	//ディザリングで徐々に消していき、消えたら削除
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
		//ボタンが押されたらディザリングのオン
		g_goMgr.FindGameObjects<Button>("button1", [&](Button* button)->bool {
			if (button->GetState() == button->enState_1) {
				m_skinModel.DitheringOn();
				m_skinModel.DecDitheringPow();
			}
			return true;
			});
	}
}
void Wall::Init()
{
	m_skinModel.Init(L"Assets/modelData/UCW_Wall0.cmo");
	m_skinModel.LoadNormalMap(L"Assets/modelData/Stone_floor_n.dds");
	m_physicsStaticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
	//ちょっと変換
	auto y = m_scale.z;
	m_scale.z = m_scale.y;
	m_scale.y = y;
}