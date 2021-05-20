#pragma once
#include "graphics/2D/Sprite.h"
#include "player/Player.h"
class Game;

class GameOver final : public IGameObject
{
public:
	GameOver();
	~GameOver();
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
	/// <summary>
	/// ボタン表示フラグの取得
	/// </summary>
	/// <returns>ボタン表示フラグ</returns>
	bool GetButtonFlag()
	{
		return m_buttonFlag;
	}
	/*
	* @enum EnSprite
	* スプライトの種類
	*/
	enum EnSprite {
		enSprite_gameOver,		//ゲームオーバー
		enSprite_button,		//ボタン
		enSprite_Num			//スプライトの数
	};
private:
	Sprite m_sprite[enSprite_Num];			//スプライト
	CVector3 m_position[enSprite_Num];		//位置
	CQuaternion m_rotation[enSprite_Num];	//回転
	CVector3 m_scale[enSprite_Num];			//拡大率
	Player* m_player = nullptr;				//プレイヤー
	/// <summary>
	/// アルファ値ステート
	/// </summary>
	enum EnState
	{
		enState_kieru,			//消える
		enState_kokunaru		//濃くなる
	};
	EnState m_state = enState_kokunaru;		//alphaステート
	float m_rotSpeed = -15.0f;				//回転速度
	float m_rotCount = 0;					//回転カウント
	float m_buttonAlpha = 0.1f;				//ボタンのalpha値
	bool m_buttonFlag = false;				//点滅フラグ

};

