#pragma once
#include "../player/Player.h"
#include "sound/SoundSource.h"
#include "../player/FireBall.h"
#include "GameData.h"
#include "../gimmick/Warp.h"
class EnemyBall;
class Game;

namespace {
	const float ENEMY_COLLIDER_RADIUS = 28.0f;		//カプセルコライダーの半径
	const float ENEMY_COLLIDER_HIGHT = 30.0f;		//カプセルコライダーの高さ
	const float SPRITE_INIT_ROT_DEG = 180.0f;		//スプライト初期回転
}

class EnemyBase : public IGameObject
{
public:
	~EnemyBase() {};
	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw() override;
	void Draw2D();
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 拡大率の設定
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	/*!
	*@brief キャラコンの初期化
	*@param[in]	pos	座標
	*/
	void InitCharaCon(const CVector3& pos)
	{
		//キャラクターコントローラー
		if (g_gameData.GetStageNo() != g_gameData.enStage_One) {
			m_charaCon.Init(
				ENEMY_COLLIDER_RADIUS,			//半径
				ENEMY_COLLIDER_HIGHT,			//高さ
				pos		//初期座標
			);
		}
		else {
			m_charaCon.Init(
				0.0f,	//半径
				0.0f,	//高さ
				pos		//初期座標
			);
		}
	}
	/// <summary>
	/// スキンモデルの取得
	/// </summary>
	/// <returns>スキンモデル</returns>
	SkinModel* GetSkinModel() 
	{
		return &m_skinModel;
	}
	/// <summary>
	/// EnemyBallのセット
	/// </summary>
	/// <param name="enemyBall">EnemyBall</param>
	void SetEnemyBall(EnemyBall* enemyBall)
	{
		m_enemyBall = enemyBall;
	}

protected:
	/// <summary>
	/// 攻撃
	/// </summary>
	virtual void Attack() = 0;
	/// <summary>
	///	死亡
	/// </summary>
	/// <param name="score">スコア</param>
	virtual void Death(int score) = 0;
	/// <summary>
	/// 回転
	/// </summary>
	virtual void Rotation() = 0;
	/// <summary>
	/// プレイヤーに伸びるベクトル&正規化    
	/// </summary>
	void VectorToPlayer()
	{
		m_v = m_player->GetPositon() - m_position;
		m_len = m_v.Length();
		m_v.Normalize();
	}
	/// <summary>
	/// 角度を求める
	/// </summary>
	void Angle()
	{
		m_naiseki = m_v.Dot(m_up);
		m_angle = acos(m_naiseki);
	}
	/// <summary>
	/// 玉に当たって死ぬ
	/// </summary>
	void DeathEnemyBallContact(int score);
	/// <summary>
	/// ファイアーボールで死ぬ
	/// </summary>
	/// <param name="score">スコア</param>
	void DeathFireBall(int score);

	SkinModel m_skinModel;								//スキンモデル。		
	CharacterController m_charaCon;						//キャラクターコントローラー
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_v = CVector3::Zero();					//ベクトル
	CVector3 m_up = CVector3::AxisY();					//上方向
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	Player* m_player = nullptr;				//プレイヤー
	Game* m_game = nullptr;					//ゲーム
	EnemyBall* m_enemyBall = nullptr;		//甲羅
	FireBall* m_fireBall = nullptr;			//ファイアーボール
	CSoundSource* m_fumuSE = nullptr;		//効果音
	bool m_isDeath = false;					//死んだ
	int m_timer = 0;						//死亡タイマー　単位：秒
	float m_gravity = 0.0f;					//重力
	float m_len = 0.0f;						//距離
	float m_naiseki = 0.0f;					//内積を求める
	float m_angle = 0.0f;					//角度
	Sprite m_sprite;										//スプライト
	CQuaternion m_spriteRot = CQuaternion::Identity();		//回転		
	Sprite m_spriteBack;									//スプライト
	CQuaternion m_spriteBackRot = CQuaternion::Identity();	//回転		
	float m_rotSpeed = 0.0f;								//回転速度
	float m_backRotSpeed = SPRITE_INIT_ROT_DEG;				//回転速度
	bool m_isDisplay = false;								//表示？
};

