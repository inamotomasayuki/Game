#include "stdafx.h"
#include "Sky.h"

const float SKY_BRIGHTNESS_POW = 1.5f;

Sky::Sky()
{
	m_skinModel.Init(L"Assets/modelData/skybox.cmo");
}


Sky::~Sky()
{
}

void Sky::Update()
{
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

void Sky::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Sky
	);
	m_skinModel.SetBrightnessPow(SKY_BRIGHTNESS_POW);
	m_skinModel.RimLightOff();
	m_skinModel.ShadowReciverOff();
}