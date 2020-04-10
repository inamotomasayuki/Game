#pragma once
#include "level/Level.h"
#include "GameCamera.h"
#include "Coin.h"
#include "Player.h"
#include "enemy/Enemy01.h"
#include "enemy/Enemy02.h"
#include "enemy/Enemy03.h"
#include "enemy/EnemyBall.h"
#include "BackGround.h"
#include "MoveFloor.h"
#include "JumpFloor.h"
#include "ShadowMap.h"
#include "SpriteUI.h"
#include "GameOver.h"
#include "GameClear.h"
#include "Star.h"
#include "Warp00.h"
#include "Warp01.h"
#include "Box.h"
#include "Item.h"
#include "Sky.h"
#include "Fade.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

const int HP_UPPER = 5;
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
		if (m_hp > HP_UPPER) {
			m_hp = HP_UPPER;
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
	/// <summary>
	/// サウンド初期化
	/// </summary>
	void InitSound();
	/// <summary>
	/// サウンド再生
	/// </summary>
	void SoundPlay();
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
	Warp00* m_warp00 = nullptr;				//ワープ0床
	Warp01* m_warp01 = nullptr;				//ワープ１床
	GameOver* m_gameOver = nullptr;			//ゲームオーバー
	GameClear* m_gameClear = nullptr;		//ゲームクリア
	Star* m_star = nullptr;					//星
	Box* m_box = nullptr;					//箱
	Sky* m_sky = nullptr;					//空
	Fade* m_fade = nullptr;					//フェード
	Item* m_item = nullptr;					//アイテム
	CSoundSource* m_bgm = nullptr;						//BGM	
	enum EnSE{
		enSE_gameClear,		//ゲームクリア音
		enSE_gameOver,		//ゲームオーバー音
		enSE_Num			//効果音の数
	};				
	CSoundSource* m_se[enSE_Num];			//効果音

private:
	int m_score = 0;				//スコア
	int m_hp = 5;					//HP
	int m_clearTimer = 0;			//クリアまでのタイマー
	int m_fireBallTimer = 0;		//ファイアボール生成タイマー
	bool m_isFireBall = false;				//ファイアボール生成中？
	bool m_gameOverFlag = false;	//ゲームオーバーフラグ
	bool m_gameClearFlag = false;	//ゲームクリアフラグ
	bool m_getStar = false;			//星を取ったかどうか
	bool m_isGameClearSE = false;	//SE鳴らしたか
	bool m_isGameOverSE = false;	//SE鳴らしたか
	bool m_isFade = false;			//フェード
	CVector3 m_cameraPos;			//カメラの位置
	CVector3 m_nextCameraPos;		//次のカメラの位置
	bool m_isGo = false;					//行けるかどうか

};
