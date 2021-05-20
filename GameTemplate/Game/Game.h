#pragma once
#include "level/Level.h"
#include "GameCamera.h"
#include "item/Coin.h"
#include "player/Player.h"
#include "enemy/Enemy01.h"
#include "enemy/Enemy02.h"
#include "enemy/Enemy03.h"
#include "enemy/Enemy04.h"
#include "enemy/EnemyBall.h"
#include "stage/BackGround.h"
#include "gimmick/MoveFloor.h"
#include "gimmick/JumpFloor.h"
#include "graphics/ShadowMap.h"
#include "result/GameClear.h"
#include "result/GameOver.h"
#include "item/Star.h"
#include "item/Item.h"
#include "stage/Sky.h"
#include "UI/Fade.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "UI/SpriteUI.h"
#include "UI/FontUI.h"
#include "gimmick/Bridge.h"
#include "gimmick/Wall.h"
#include "UI/menu/UIManager.h"
#include "gimmick/Warp.h"
#include "gimmick/Box.h"

namespace {
	const int HP_UPPER = 5;		//HP上限
}
class Game final : public IGameObject
{
public:
	Game();
	~Game();
	/*
	* @brief 更新
	*/
	void Update() override;
	/*!
	* @ brief 毎フレーム１回だけ更新
	*	オブジェクトを生成するコードがあるため
	*/
	void NewUpdate() override;
	/*!
	* @brief 描画
	*/
	void Draw() override;
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
	int GetScore() const
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
	int GetHP() const 
	{
		return m_hp;
	}
	/// <summary>
	/// ゲームオーバーかどうか
	/// </summary>
	/// <returns></returns>
	bool GetGameOverFlag() const
	{
		return m_gameOverFlag;
	}
	/// <summary>
	/// ゲームクリアしたかどうか
	/// </summary>
	/// <returns></returns>
	bool GetGameClearFlag() const
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
	bool GetStar() const
	{
		return m_getStar;
	}
	/// <summary>
	/// ボタン設定
	/// </summary>
	/// <param name="button"></param>
	void SetIsButton(bool button)
	{
		m_isButton = button;
	}
	/// <summary>
	/// ボタン設定を取得
	/// </summary>
	/// <returns></returns>
	bool GetIsButton() const
	{
		return m_isButton;
	}
	/// <summary>
	/// 止まってるか取得
	/// </summary>
	/// <returns>止まってるか</returns>
	bool GetIsStop() const
	{
		return m_isStop;
	}
	/// <summary>
	/// HP０によるゲームオーバーか取得
	/// </summary>
	/// <returns>HP０によるゲームオーバーか</returns>
	bool GetIsHp0GameOver() const
	{
		return m_isHp0GameOver;
	}
	/// <summary>
	/// 星を取ったか取得
	/// </summary>
	/// <returns>星を取ったか</returns>
	bool GetIsStar() const
	{
		return m_isGetStar;
	}
private:
	/// <summary>
	/// ステージ01初期化
	/// </summary>
	void Stage01Init();
	/// <summary>
	/// ステージ02初期化
	/// </summary>
	void Stage02Init();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 削除
	/// </summary>
	void Delete();
	/// <summary>
	/// サウンド初期化
	/// </summary>
	void InitSound();
	/// <summary>
	/// サウンド再生
	/// </summary>
	void SoundPlay();
private:
	Level m_level;							//レベル
	Player* m_player = nullptr;				//プレイヤー
	Coin* m_coin = nullptr;					//コイン
	Enemy01* m_enemy01 = nullptr;			//敵01
	Enemy02* m_enemy02 = nullptr;			//敵02
	Enemy03* m_enemy03 = nullptr;			//敵03
	Enemy04* m_enemy04 = nullptr;			//敵04
	GameCamera* m_gameCamera = nullptr;		//ゲームカメラ
	BackGround* m_stage01[BackGround::enStage01Obj_Num] = { nullptr };		//ステージ1
	BackGround* m_stage02[BackGround::enStage02Obj_Num] = { nullptr };		//ステージ2
	MoveFloor* m_moveFloor = nullptr;		//動く床
	SpriteUI* m_spriteUI = nullptr;			//スプライト
	JumpFloor* m_jumpFloor = nullptr;		//ジャンプ床
	Warp* m_warp = nullptr;					//ワープ床
	GameOver* m_gameOver = nullptr;			//ゲームオーバー
	GameClear* m_gameClear = nullptr;		//ゲームクリア
	Star* m_star = nullptr;					//星
	Box* m_box = nullptr;					//箱
	Sky* m_sky = nullptr;					//空
	Fade* m_fade = nullptr;					//フェード
	Item* m_item = nullptr;					//アイテム
	FontUI* m_fontUI = nullptr;				//フォント
	Bridge* m_bridge = nullptr;				//橋
	Button* m_button = nullptr;				//ボタン
	Wall* m_wall = nullptr;					//壁
	UIManager* m_uiManager = nullptr;		//UIマネージャー
	CSoundSource* m_bgm = nullptr;			//BGM	
	enum EnSE{
		enSE_gameClear,		//ゲームクリア音
		enSE_gameOver,		//ゲームオーバー音
		enSE_menu,			//メニュー開く音
		enSE_Num			//効果音の数
	};				
	CSoundSource* m_se[enSE_Num];			//効果音
private:
	int m_score = 0;				//スコア
	int m_hp = HP_UPPER;			//HP
	int m_stopTime = 0;				//止める
	int m_clearTimer = 0;			//クリアまでのタイマー
	bool m_gameOverFlag = false;	//ゲームオーバーフラグ
	bool m_isHp0GameOver = false;	//HP０によるゲームオーバーか
	bool m_gameClearFlag = false;	//ゲームクリアフラグ
	bool m_getStar = false;			//星を取ったかどうか
	bool m_isGameClearSE = false;	//SE鳴らしたか
	bool m_isGameOverSE = false;	//SE鳴らしたか
	bool m_isFade = false;			//フェード
	bool m_isGo = false;			//行けるかどうか
	bool m_isButton = false;		//ボタン押したか
	bool m_isStop = false;			//止まってるか
	bool m_isGetStar = false;		//星取ったか
};
