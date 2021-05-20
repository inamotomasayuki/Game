#include "stdafx.h"
#include "FontUI.h"
#include "../time/GameTime.h"
#include "Game.h"
#include "../gimmick/Button.h"

namespace 
{
	const int MINUTE_AND_SECOND = 60;								//分・秒
	const float BUTTON_TIMER = 0.98f;								//タイマー
	const float BUTTON_SCALE_MULTIPLY = 2.0f;						//ボタンスケール乗算
	const float BUTTON_SCALE_ATTENUTANION = 0.98f;					//ボタンスケール徐々に小さく
	const CVector2 BUTTON_TIMER_POS = { 610.0f,250.0f };			//ボタンタイマー位置
	const CVector4 BUTTON_TIMER_COLOR = { 1.0f,0.0f,0.0f,1.0f };	//ボタンタイマーの色
	const CVector2 BUTTON_PIVOT = { 0.5f,0.5f };					//ボタンのピボット
	const CVector2 PLAYTIME_POS = { 400.0f, 0.0f };					//プレイ時間の位置
	const CVector4 PLAYTIME_COLOR = { 0.0f,1.0f,0.0f,1.0f };		//プレイ時間の色
	const int TEXT_SIZE = 256;										//テキスト
}
FontUI::FontUI()
{
	m_fontScale = CVector2::One() * BUTTON_SCALE_MULTIPLY;
}


FontUI::~FontUI()
{
}

void FontUI::Update()
{
	m_game = g_goMgr.FindGameObject<Game>("game");
	//ボタンタイマー
	if (m_game->GetIsButton()) {
		m_scaleTimer += GameTime().GetFrameDeltaTime();
		if (m_scaleTimer >= BUTTON_TIMER) {
			//戻す
			m_fontScale = CVector2::One() * BUTTON_SCALE_MULTIPLY;
			m_scaleTimer = 0.0f;
		}
		else if (m_scaleTimer > 0.0f) {
			//徐々に縮小
			m_fontScale *= BUTTON_SCALE_ATTENUTANION;
		}
		else {
			m_scaleTimer = 0.0f;
		}
	}
	if (!m_game->GetGameClearFlag() && !m_game->GetGameOverFlag()) {
		m_timer += GameTime().GetFrameDeltaTime();
	}
}
void FontUI::DrawFont()
{
	if (m_game != nullptr) {
		if (!m_game->GetGameOverFlag()) {
			//ボタン押したときのタイマー
			g_goMgr.FindGameObjects<Button>("button", [&](Button* button)->bool {
				if (button->GetState() == button->enState_0) {
					if (button->GetIsPush()) {
						wchar_t text[256];
						int sec = (int)button->GetTimer() % MINUTE_AND_SECOND;
						swprintf_s(text, L"%01d", sec);
						m_font.DrawScreenPos(
							text,
							BUTTON_TIMER_POS,
							BUTTON_TIMER_COLOR,
							m_fontScale,
							BUTTON_PIVOT
						);
					}
				}
				return true;
				});
		}
	}
	//プレイ時間
	wchar_t text[TEXT_SIZE];
	int minute = (int)m_timer / MINUTE_AND_SECOND;
	int sec = (int)m_timer % MINUTE_AND_SECOND;
	swprintf_s(text, L"プレイ時間　%02d:%02d", minute, sec);
	m_font.DrawScreenPos(
		text,
		PLAYTIME_POS,
		PLAYTIME_COLOR
	);
}