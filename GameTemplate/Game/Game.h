#pragma once
#include "level/Level.h"
#include "GameCamera.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy01.h"
#include "Enemy02.h"
#include "BackGround.h"
#include "MoveFloor.h"
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
	/// <summary>
	/// スコアの設定
	/// </summary>
	/// <param name="i">加算するスコアの値</param>
	void SetScore(int i)
	{
		m_score += i;
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
	int m_score = 0;			//スコア
};