#include "stdafx.h"
#include "FontUI.h"


FontUI::FontUI()
{
}


FontUI::~FontUI()
{
}

void FontUI::Update()
{
}

void FontUI::DrawFade()
{
	//m_timer = max(0.0f, m_timer - GameTime().GetFrameDeltaTime());
	m_timer += GameTime().GetFrameDeltaTime() * 2.0f;
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