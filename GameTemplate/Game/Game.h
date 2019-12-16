#pragma once
#include "level/Level.h"
#include "GameCamera.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy01.h"
#include "Enemy02.h"
#include "Enemy03.h"
#include "EnemyBall.h"
#include "BackGround.h"
#include "MoveFloor.h"
#include "JumpFloor.h"
#include "ShadowMap.h"
#include "SpriteUI.h"
#include "GameOver.h"
#include "GameClear.h"
#include "Star.h"
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
	/// <summary>
	/// ゲームオーバーかどうか
	/// </summary>
	/// <returns></returns>
	bool GetGameOverFlag()
	{
		return m_gameOverFlag;
	}
	/// <summary>
	/// ゲームクリアしたかどうか
	/// </summary>
	/// <returns></returns>
	bool GetGameClearFlag()
	{
		return m_gameClearFlag;
	}
	/// <summary>
	/// 星を取ったフラグの設定
	/// </summary>
	void SetGetStarFlag()
	{
		m_getStar = true;
	}
	/// <summary>
	/// 星を取ったかどうか
	/// </summary>
	/// <returns></returns>
	bool GetStar()
	{
		return m_getStar;
	}
private:
	Level m_level;
	Player* m_player = nullptr;				//プレイヤー
	Coin* m_coin = nullptr;					//コイン
	Enemy01* m_enemy01 = nullptr;			//敵01
	Enemy02* m_enemy02 = nullptr;			//敵02
	Enemy03* m_enemy03 = nullptr;			//敵03
	GameCamera* m_gameCamera = nullptr;		//ゲームカメラ
	BackGround* m_backGround = nullptr;		//ステージ
	MoveFloor* m_moveFloor = nullptr;		//動く床
	SpriteUI* m_spriteUI = nullptr;			//スプライト
	JumpFloor* m_jumpFloor = nullptr;		//ジャンプ床
	GameOver* m_gameOver = nullptr;			//ゲームオーバー
	GameClear* m_gameClear = nullptr;		//ゲームクリア
	Star* m_star = nullptr;					//星
private:
	int m_score = 0;			//スコア
	int m_hp = 3;				//HP
	int m_clearTimer = 0;		//クリアまでのタイマー
	bool m_gameOverFlag = false;	//ゲームオーバーフラグ
	bool m_gameClearFlag = false;	//ゲームクリアフラグ
	bool m_getStar = false;			//星を取ったかどうか
	CVector3 m_cameraPos;			//カメラの位置
	CVector3 m_nextCameraPos;		//次のカメラの位置
};
