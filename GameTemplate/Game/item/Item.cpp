#include "stdafx.h"
#include "Item.h"
#include "../gimmick/Box.h"
#include "../player/Player.h"

namespace {
	const float MOVE_SPEED = 2.0f;				//上がる速度
	const float DOWN_SPEED = 5.0f;				//下がる速度
	const float ROTATION_SPEED = 3.0f;			//回転速度
	const float DLIG_COLOR = 1.5f;				//ディレクションライトの明るさ
}

Item::Item()
{
	m_skinModel.Init(L"Assets/modelData/mikan.cmo");
	m_se = g_goMgr.NewGameObject<CSoundSource>(0);
	m_se->Init(L"Assets/sound/kyodaika.wav");		//巨大化
}


Item::~Item()
{
}

void Item::Update()
{
	const auto& player = g_goMgr.FindGameObject<Player>("player");
	if (m_isHipDrop) {
		if (m_posDown < m_position.y) {
			m_position.y -= DOWN_SPEED;
		}
		else {
			//ゴースト作成
			if (!m_isInit) {
				m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
				m_isInit = true;
			}
		}
	}
	else{
		if (!m_isInit) {
			m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
			m_isInit = true;
		}
		if (player != nullptr) {
			//上がっていく
			if (m_posUp > m_position.y) {
				m_position.y += MOVE_SPEED;
			}
		}
	}
	//削除
	if (m_isGet) {
		if (player != nullptr) {
			if (!player->GetisItem()) {
				m_se->Play(false);
			}
		}
		g_goMgr.DeleteGameObject(this);
	}
	//回転
	Rotation();
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_ghostObject.SetPosition(m_position);
}
void Item::Rotation()
{
	//一定速度で回転させる
	float rotSpeed = 0.0f;;
	rotSpeed += ROTATION_SPEED;
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), rotSpeed);
	m_rotation.Multiply(addRot);
}
void Item::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//リムライトオフ
	m_skinModel.RimLightOff();
	//オフ
	m_skinModel.ToonOff();
	m_skinModel.ShadowReciverOff();
	//ライトの方向・明るさ設定
	m_skinModel.SetDligColor(0, DLIG_COLOR);
	m_skinModel.SetDligColor(1, DLIG_COLOR);
}