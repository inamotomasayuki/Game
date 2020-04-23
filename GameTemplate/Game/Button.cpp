#include "stdafx.h"
#include "Button.h"
#include "Game.h"
const float BUTTON_DOWN_POS = -7.0f;	//ボタン下げる位置		
const float LIMIT_TIMER = 11.0f;				//制限時間
Button::Button()
{
	m_skinModel.Init(L"Assets/modelData/button.cmo");
	m_fumuSE = g_goMgr.NewGameObject<CSoundSource>(0);
	m_fumuSE->Init(L"Assets/sound/fumu.wav");
	m_physicsStaticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
	m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
	m_state = enState_stop;
}


Button::~Button()
{
}

void Button::Update()
{
	m_game = g_goMgr.FindGameObject<Game>("game");
	if (m_state == enState_0 || m_state == enState_1) {
		if (!m_game->GetIsButton()) {
			if (!m_isSE) {
				m_fumuSE->Play(false);
				m_isSE = true;
				m_game->SetIsButton(true);
			}
		}
		if (!m_isDown) {
			m_position.y = m_initPos.y + BUTTON_DOWN_POS;
			m_isDown = true;
		}
		m_timer -= GameTime().GetFrameDeltaTime() * 2.0f;
	}
	else if (m_state == enState_stop) {		
		if (m_isDelete) {
			g_goMgr.DeleteGameObject(this);
		}
		m_position.y = m_initPos.y;
	}
	if (m_state == enState_1) {
		m_isDelete = true;
	}
	if (m_timer <= 1.0) {
		m_timer = LIMIT_TIMER;
		m_game->SetIsButton(false);
		m_isSE = false;
		m_isDown = false;
		m_isPush = false;
		m_state = enState_stop;
	}

	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);
	m_ghostObject.SetPosition(m_position);
}

void Button::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	m_skinModel.RimLightOff();
}
