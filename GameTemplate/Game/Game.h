#pragma once
#include "level/Level.h"
#include "GameCamera.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy01.h"
#include "Enemy02.h"
#include "BackGround.h"
#include "MoveFloor.h"
#include "JumpFloor.h"
#include "ShadowMap.h"
#include "SpriteUI.h"
#include "GameOver.h"
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
public:
	/// <summary>
	/// スコアの設定
	/// </summary>
	/// <param name="i">加算するスコアの値</param>
	void SetScore(int score)
	{
		m_score += score;
		if (m_score < 0) {
			m_score = 0;
		}
	}
	/// <summary>
	/// スコアの取得
	/// </summary>
	/// <returns>スコアの値</returns>
	int GetScore()
	{
		return m_score;
	}
	/// <summary>
	/// Hpの設定
	/// </summary>
	/// <param name="hp">HP</param>
	void SetHP(int hp) 
	{
		m_hp += hp;

		if (m_hp < 0) {
			m_hp = 0;
		}
	}
	/// <summary>
	/// HPの取得
	/// </summary>
	/// <returns></returns>
	int GetHP()
	{
		return m_hp;
	}
	bool GetGameOverFlag()
	{
		return m_gameOverFlag;
	}
private:
	Level m_level;
	Player* m_player = nullptr;				//プレイヤー
	Coin* m_coin = nullptr;					//コイン
	Enemy01* m_enemy01 = nullptr;			//敵01
	Enemy02* m_enemy02 = nullptr;			//敵02
	GameCamera* m_gameCamera = nullptr;		//ゲームカメラ
	BackGround* m_backGround = nullptr;		//ステージ
	MoveFloor* m_moveFloor = nullptr;		//動く床
	SpriteUI* m_spriteUI = nullptr;			//スプライト
	JumpFloor* m_jumpFloor = nullptr;		//ジャンプ床
	GameOver* m_gameOver = nullptr;			//ゲームオーバー
private:
	int m_score = 0;			//スコア
	int m_hp = 3;				//HP
	bool m_gameOverFlag = false;	//ゲームオーバーフラグ
};
