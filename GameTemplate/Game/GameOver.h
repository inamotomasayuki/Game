#pragma once
#include "graphics/2D/Sprite.h"
#include "Player.h"
class Game;

class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();
	void Update();
	void Draw() {};
	void Draw2D();	
	/// <summary>
	/// ボタン表示フラグの取得
	/// </summary>
	/// <returns>ボタン表示フラグ</returns>
	bool GetButtonFlag()
	{
		return m_buttonFlag;
	}
	enum EnSprite {
		enSprite_gameOver,		//ゲームオーバー
		enSprite_button,		//ボタン
		enSprite_Num
	};

private:
	Sprite m_sprite[enSprite_Num];							//スプライト
	CVector3 m_position[enSprite_Num];						//位置
	CQuaternion m_rotation[enSprite_Num];					//回転
	CVector3 m_scale[enSprite_Num];						//拡大率
	float m_rotSpeed = -15.0f;				//回転速度
	float m_rotCount = 0;					//回転カウント
	float m_buttonAlpha = 0.1f;			//ボタンのalpha値
	bool m_buttonFlag = false;					//点滅フラグ
	Player* m_player = nullptr;
	enum EnState
	{
		enState_kieru,			//消える
		enState_kokunaru		//濃くなる
	};
	EnState m_state = enState_kokunaru;		//alphaステート

};

