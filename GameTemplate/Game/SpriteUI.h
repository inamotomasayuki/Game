#pragma once
#include "graphics/2D/Sprite.h"

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
		enSprite_Num
	};

private:
	/// <summary>
/// 半透明合成のブレンドステートを初期化。
/// </summary>
	void InitTranslucentBlendState();
private:
	Sprite m_spriteUI[enSprite_Num];
	CVector3 m_position[enSprite_Num];
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	ID3D11BlendState* m_translucentBlendState = nullptr;	//半透明合成用のブレンドステート。
};

