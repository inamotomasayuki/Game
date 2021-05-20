#pragma once
#include "graphics/2D/Sprite.h" 
class GameClear final : public IGameObject
{
public:
	GameClear();
	~GameClear();
	/*!
	*@brief 更新
	*/
	void Update() override;
	/*!
	*@brief 描画
	*/
	void Draw() override {};
	/*!
	*@brief 2D描画
	*/
	void Draw2D() override;
	/*!
	* enum EnSprite
	*　スプライトの種類
	*/
	enum EnSprite {
		enSprite_clear,			//クリア
		enSprite_button,		//ボタン
		enSprite_Num			//スプライトの数
	};
private:
	/*!
	* enum EnAlphaState
	* アルファ値ステート
	*/
	enum EnAlphaState
	{
		enAlphaState_kieru,				//消える
		enAlphaState_kokunaru			//濃くなる
	};
	EnAlphaState m_alphaState = enAlphaState_kokunaru;		//alphaステート
	/*!
	* enum EnScaleState
	* 拡大率ステート
	*/
	enum EnScaleState
	{
		enScaleState_up,			//拡大
		enScaleState_down			//縮小
	};
	EnScaleState m_scaleState = enScaleState_up;		//スケールステート
	Sprite m_sprite[enSprite_Num];						//スプライト
	CVector3 m_position[enSprite_Num];					//位置
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale[enSprite_Num];						//スケール
	bool m_buttonFlag = false;							//点滅フラグ
	int m_scaleTimer = 0;								//スケールタイマー　単位：秒
	float m_buttonAlpha = 0.1f;							//ボタンのalpha値
};

