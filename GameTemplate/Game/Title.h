#pragma once
#include "graphics/2D/Sprite.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
class Title : public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Draw();

private:
	Sprite m_sprite;		//スプライト
	CSoundSource m_bgm;		//BGM
};

