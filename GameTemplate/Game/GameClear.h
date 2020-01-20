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
		enSprite_clear,			//クリア
		enSprite_button,		//ボタン
		enSprite_Num			//スプライトの数
	};
private:
	Sprite m_sprite[enSprite_Num];							//スプライト
	CVector3 m_position[enSprite_Num];						//位置
	CQuaternion m_rotation = CQuaternion::Identity();		//回転
	CVector3 m_scale[enSprite_Num];							//スケール
	float m_buttonAlpha = 0.1f;								//ボタンのalpha値
	bool m_buttonFlag = false;								//点滅フラグ

	enum EnAlphaState
	{
		enAlphaState_kieru,				//消える
		enAlphaState_kokunaru			//濃くなる
	};
	EnAlphaState m_alphaState = enAlphaState_kokunaru;		//alphaステート
	
	enum EnScaleState
	{
		enScaleState_up,			//拡大
		enScaleState_down			//縮小
	};
	EnScaleState m_scaleState = enScaleState_up;		//スケールステート
	int m_scaleTimer = 0;								//スケールタイマー　単位：秒
};

