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
	float m_buttonAlpha = 0.1f;			//ボタンのalpha値
	bool m_buttonFlag = false;					//点滅フラグ

	enum EnAlphaState
	{
		enAlphaState_kieru,
		enAlphaState_kokunaru
	};
	EnAlphaState m_alphaState = enAlphaState_kokunaru;		//alphaステート
	
	enum EnScaleState
	{
		enScaleState_up,
		enScaleState_down
	};
	EnScaleState m_scaleState = enScaleState_up;		//スケールステート
	int m_scaleTimer = 0;			//スケールタイマー　単位：秒
};

