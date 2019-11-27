#pragma once
#include "graphics/2D/Sprite.h"
class Title : public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Draw();

private:
	Sprite m_sprite;		//スプライト
	Game* m_game = nullptr;
};

