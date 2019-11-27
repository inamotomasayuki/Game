#pragma once
#include "graphics/2D/Sprite.h"
class Game;
class SpriteUI : public IGameObject
{
public:
	SpriteUI();
	~SpriteUI();
	void Update();
	void Draw();
	enum EnSprite {
		enSprite_unityChan,
		enSprite_kakeru,
		enSprite_coin,
		enSprite_Num
	};
	enum EnSpriteNum {
		enSpriteNum_zero,
		enSpriteNum_one,
		enSpriteNum_two,
		enSpriteNum_three,
		enSpriteNum_four,
		enSpriteNum_five,
		enSpriteNum_six,
		enSpriteNum_seven,
		enSpriteNum_eight,
		enSpriteNum_nine,
		enSpriteNum_Num,
	};
private:
	/// <summary>
/// 半透明合成のブレンドステートを初期化。
/// </summary>
	void InitTranslucentBlendState();
private:
	Sprite m_spriteUI[enSprite_Num];
	Sprite m_spriteNumUI[enSpriteNum_Num];
	Sprite m_spriteNumUI2[enSpriteNum_Num];
	CVector3 m_positionUI[enSprite_Num];
	CVector3 m_positionNum;
	CVector3 m_positionNum2;
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	ID3D11BlendState* m_translucentBlendState = nullptr;	//半透明合成用のブレンドステート。
	int m_counter = 0;
	Game* m_game = nullptr;
};

