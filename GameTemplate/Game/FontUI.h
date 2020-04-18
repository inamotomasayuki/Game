#pragma once
#include "Font.h"
#include "GameTime.h"
class FontUI : public IGameObject
{
public:
	FontUI();
	~FontUI();
	void Update();
	void Draw() {}
	void DrawFade();
private:
	float m_timer = 0.0f;
	Font m_font;
};

