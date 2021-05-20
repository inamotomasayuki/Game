#include "stdafx.h"
#include "Sky.h"
#include "GameData.h"
namespace {
	const float ROTATION_SPEED = 0.001f;					//回転速度
}
Sky::Sky()
{
	m_skinModel.Init(L"Assets/modelData/UCW_Sky.cmo");
}


Sky::~Sky()
{
}

void Sky::Update()
{
	//一定速度で回転させる
	float rotSpeed = 0.0f;;
	rotSpeed += ROTATION_SPEED;
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
	m_rotation.Multiply(addRot);

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
	//リムライトオフ
	m_skinModel.RimLightOff();
	//レシーバーオフ
	m_skinModel.ShadowReciverOff();
}