#include "stdafx.h"
#include "BackGround.h"
#include "GameData.h"

BackGround::BackGround()
{
	if (g_gameData.GetStageNo() == 0) {
		m_skinModel.Init(L"Assets/modelData/gameStage02.cmo");
	}
	if (g_gameData.GetStageNo() == 1) {	
		m_skinModel.Init(L"Assets/modelData/gameStage03.cmo");
	}
	m_physicsStaticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
}


BackGround::~BackGround()
{
}
void BackGround::Update()
{
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}
void BackGround::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	m_skinModel.RimLightOff();
}