#include "stdafx.h"
#include "Warp01.h"

const float ROTATION_SPEED = 2.0f;					//回転速度
const float LENGTH_NEAR = 50.0f;				//近い	
const float LENGTH_LEAVE = 100.0f;				//離れた
const float EFFECT_SCALE = 10.0f;				//エフェクトの大きさ

Warp01::Warp01()
{
	m_skinModel.Init(L"Assets/modelData/warp.cmo");
	m_effect = g_goMgr.NewGameObject<Effect>(0);
	//エフェクトをロードする。
	m_effect->SetFilePath(L"Assets/effect/uzu.efk");
}


Warp01::~Warp01()
{
	g_goMgr.DeleteGameObject(m_effect);
}

void Warp01::Update()
{
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//回転
	Rotation();
	m_player = g_goMgr.FindGameObject<Player>("player");
	if (m_player != nullptr) {
		auto v = m_position - m_player->GetPositon();
		auto len = v.Length();
		if (len < LENGTH_NEAR
			&& !m_player->GetIsLeave01()) {
			m_player->SetIsWarp01(true);
		}
		if (len >= LENGTH_LEAVE) {
			m_player->SetIsLeave01(false);
		}
	}
	//エフェクトを再生する。
	m_effect->PlayAndSetPos(m_position);
	m_effect->SetScale(m_scale * EFFECT_SCALE);

}
void Warp01::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	m_skinModel.RimLightOff();
}
void Warp01::Rotation()
{
	//一定速度で回転させる
	float rotSpeed = 0.0f;;
	rotSpeed += ROTATION_SPEED;
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
	m_rotation.Multiply(addRot);
}