#include "stdafx.h"
#include "FontUI.h"
#include "GameTime.h"
#include "Game.h"

FontUI::FontUI()
{
}


FontUI::~FontUI()
{
}

void FontUI::Update()
{
	m_game = g_goMgr.FindGameObject<Game>("game");
	if (m_game->GetIsButton()) {
		m_scaleTimer += GameTime().GetFrameDeltaTime() * 2.0f;
		if (m_scaleTimer >= 0.99f) {
			m_fontScale = CVector2::One() * 2;
			m_scaleTimer = 0.0f;
		}
		else if (m_scaleTimer > 0.0f) {
			m_fontScale *= 0.98f;
		}
		else {
			m_scaleTimer = 0.0f;
		}
	}
}
void FontUI::DrawFont()
{
	g_goMgr.FindGameObjects<Button>("button", [&](Button* button)->bool {
		if (button->GetState() == button->enState_0) {
			if (button->GetIsPush()) {
				wchar_t text[256];
				int sec = (int)button->GetTimer() % 60;
				swprintf_s(text, L"%01d", sec);
				m_font.DrawScreenPos(
					text,
					{ 610.0f,250.0f },
					{ 1.0f,0.0f,0.0f,1.0f },
					m_fontScale,
					{ 0.5f,0.5f }
				);
			}
		}
		return true;
		});
	auto game = g_goMgr.FindGameObject<Game>("game");
	if (!game->GetGameClearFlag() && !game->GetGameOverFlag()) {
		m_timer += GameTime().GetFrameDeltaTime() * 2.0f;
	}
	wchar_t text[256];
	int minute = (int)m_timer / 60;
	int sec = (int)m_timer % 60;
	swprintf_s(text, L"%02d:%02d", minute, sec);
	m_font.DrawScreenPos(
		text,
		{ 670.0f,0.0f },
		{ 0.0f,1.0f,0.0f,1.0f }
	);
	m_font.DrawScreenPos(
		L"ƒvƒŒƒCŽžŠÔ",
		{ 380.0f, 0.0f },
		{ 0.0f,1.0f,0.0f,1.0f }
	);
}