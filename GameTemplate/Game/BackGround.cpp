#include "stdafx.h"
#include "BackGround.h"
#include "GameData.h"

BackGround::BackGround()
{
	if (g_gameData.GetStageNo() == 0) {
		m_skinModel.Init(L"Assets/modelData/gameStage01_final.cmo");
	}
	if (g_gameData.GetStageNo() == 1) {	
		//m_skinModel.Init(L"Assets/modelData/gameStage03.cmo");
		m_skinModel.Init(L"Assets/modelData/gameStage_02_01.cmo");
	}
	m_physicsStaticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
	m_ghostObject.CreateMesh(m_ghostPos, m_rotation, m_scale, m_skinModel);
}


BackGround::~BackGround()
{
}
void BackGround::Update()
{
	m_ghostObject.SetPosition(m_ghostPos);
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