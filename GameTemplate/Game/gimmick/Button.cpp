#include "stdafx.h"
#include "Button.h"
#include "Game.h"
#include "GameData.h"
namespace {
	const float BUTTON_DOWN_POS = -7.0f;	//ボタン下げる位置		
	const float TIME_OVER = 1.0f;			//タイムオーバー
}
Button::Button()
{
}


Button::~Button()
{
}

void Button::Update()
{
	//初期化
	Init();

	const auto& player = g_goMgr.FindGameObject<Player>("player");
	m_game = g_goMgr.FindGameObject<Game>("game");

	if (m_state == enState_0 || m_state == enState_1) {
		if (!m_game->GetIsButton()) {
			if (!m_isSE) {
				//効果音鳴らす
				m_fumuSE->Play(false);
				m_isSE = true;
				m_game->SetIsButton(true);
			}
		}
		if (!m_isDown) {
			//踏んだらボタンの位置を下げる
			m_position.y = m_initPos.y + BUTTON_DOWN_POS;
			m_isDown = true;
		}
		m_timer -= GameTime().GetFrameDeltaTime();
	}
	if (g_gameData.GetStageNo() == g_gameData.enStage_Zero) {
		if (m_state == enState_stop) {
			if (m_isDelete) {
				//壁消すボタン削除
				g_goMgr.DeleteGameObject(this);
			}
			//元の位置に上げる
			m_position.y = m_initPos.y;
		}
	}
	if (g_gameData.GetStageNo() == g_gameData.enStage_One) {
		if (m_state == enState_stop) {
			m_isSE = false;
			m_isDown = false;
			//プレイヤーがボタンに触れてなかったら元の位置に上げる
			player->SetIsButtonFalse();
			m_position.y = m_initPos.y;
		}
	}
	if (m_state == enState_1) {
		//壁消すボタンは一度押したらいらないので削除する
		m_isDelete = true;
	}
	if (m_timer <= TIME_OVER) {
		m_timer = LIMIT_TIMER;
		m_game->SetIsButton(false);
		m_isSE = false;
		m_isDown = false;
		m_isPush = false;
		m_state = enState_stop;
	}	
	if (m_state == enState_2) {
		if (!m_isSE) {
			m_fumuSE->Play(false);
			m_isSE = true;
		}
		if (!m_isDown) {
			//踏んだらボタンの位置を下げる
			m_position.y = m_initPos.y + BUTTON_DOWN_POS;
			m_isDown = true;
		}
	}
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);
	m_ghostObject.SetPosition(m_ghostPos);
}

void Button::Draw()
{
	if (m_isInit) {
		m_skinModel.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			enRenderMode_Normal
		);
		//リムライトオフ
		m_skinModel.RimLightOff();
		m_skinModel.ToonOff();
	}
}

void Button::Init()
{
	if (!m_isInit) {
		m_skinModel.Init(L"Assets/modelData/button.cmo");
		//効果音
		m_fumuSE = g_goMgr.NewGameObject<CSoundSource>(0);
		m_fumuSE->Init(L"Assets/sound/fumu.wav");

		m_physicsStaticObject.CreateMeshObject(m_skinModel, m_position, m_rotation, m_scale);
		m_ghostObject.CreateMesh(m_position, m_rotation, m_scale, m_skinModel);
		//ステートを設定
		m_state = enState_stop;
		//モデルの都合上のため変換
		auto y = m_scale.z;
		m_scale.z = m_scale.y;
		m_scale.y = y;
		//初期化したのでtrue
		m_isInit = true;
	}
}