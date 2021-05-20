#include "stdafx.h"
#include "Warp.h"
#include "../player/Player.h"
namespace {
	const float ROTATION_SPEED = 2.0f;					//回転速度
	const float LENGTH_NEAR = 50.0f;				//近い	
	const float LENGTH_LEAVE = 100.0f;				//離れた
	const float EFFECT_SCALE = 10.0f;				//エフェクトの大きさ
}

Warp::Warp()
{
	m_skinModel[enState_00].Init(L"Assets/modelData/warp.cmo");
	m_skinModel[enState_01].Init(L"Assets/modelData/warp.cmo");
	//リムライトオフ
	for (int i = 0; i < enState_Num; i++) {
		m_skinModel[i].RimLightOff();
		//エフェクト
		m_effect[i] = g_goMgr.NewGameObject<EffectEngine>(0);
		//エフェクトをロードする。
		m_effect[i]->SetFilePath(L"Assets/effect/uzu.efk");
	}
}


Warp::~Warp()
{
	for (int i = 0; i < enState_Num; i++) {
		g_goMgr.DeleteGameObject(m_effect[i]);
	}
}

void Warp::Update()
{
	//回転
	Rotation();
	//ワープ
	m_player = g_goMgr.FindGameObject<Player>("player");
	if (m_player != nullptr) {
		for (int i = 0; i < enState_Num; i++) {
			const auto& v = m_position[i] - m_player->GetPositon();
			auto len = v.Length();
			if (!m_isWarp && m_isPossible) {
				//プレイヤーが近くに来たらフラグを送る
				if (len < LENGTH_NEAR) {
					m_stateNum = i + 1;
					if (m_stateNum == enState_Num) {
						m_stateNum = 0;
					}
					m_isWarp = true;
					m_isPossible = false;
				}
			}
		}
		if (!m_isWarp && !m_isPossible) {
			//離れていたら再度ワープを可能にするフラグを送る
			const auto& v = m_position[m_stateNum] - m_player->GetPositon();
			auto len = v.Length();
			if (len > LENGTH_LEAVE) {
				m_isPossible = true;
			}
		}
	}
	//エフェクトを再生する。
	for (int i = 0; i < enState_Num; i++) {
		m_effect[i]->PlayAndSetPos(m_position[i]);
		m_effect[i]->SetScale(m_scale[i] * EFFECT_SCALE);
	}
	//ワールド行列の更新。
	for (int i = 0; i < enState_Num; i++) {
		m_skinModel[i].UpdateWorldMatrix(m_position[i], m_rotation[i], m_scale[i]);
	}

}
void Warp::Draw()
{
	for (int i = 0; i < enState_Num; i++) {
		m_skinModel[i].Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			enRenderMode_Normal
		);
	}
}
void Warp::Rotation()
{
	//一定速度で回転させる
	float rotSpeed = 0.0f;;
	rotSpeed += ROTATION_SPEED;
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
	for (int i = 0; i < enState_Num; i++) {
		m_rotation[i].Multiply(addRot);
	}
}