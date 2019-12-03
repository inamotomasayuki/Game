#pragma once
#include "graphics/2D/Sprite.h" 
class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();
	void Update();
	void Draw() {};
	void Draw2D();
	enum EnSprite {
		enSprite_clear,
		enSprite_button,
		enSprite_Num
	};
private:
	Sprite m_sprite[enSprite_Num];
	CVector3 m_position[enSprite_Num];
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale[enSprite_Num];
};

