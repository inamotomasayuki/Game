#pragma once
#include "Font.h"
#include "GameTime.h"
#include "Button.h"
class Game;
class FontUI : public IGameObject
{
public:
	FontUI();
	~FontUI();
	void Update();
	void Draw() {}
	void DrawFont();
private:
	float m_timer = 0.0f;
	Font m_font;
	CVector2 m_fontScale = CVector2::One() * 2.0f;
	float m_scaleTimer = 0.0f;
	Game* m_game = nullptr;
};

