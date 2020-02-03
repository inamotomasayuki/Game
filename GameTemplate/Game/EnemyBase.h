#pragma once
#include "Player.h"
#include "ShadowMap.h"
#include "sound/SoundSource.h"

class EnemyBall;
class Game;

const float ENEMY_COLLIDER_RADIUS = 0.0f;		//カプセルコライダーの半径
const float ENEMY_COLLIDER_HIGHT = 0.0f;		//カプセルコライダーの高さ

class EnemyBase : public IGameObject
{
public:
	~EnemyBase() {};
	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		//キャラクターコントローラー
		m_charaCon.Init(
			ENEMY_COLLIDER_RADIUS,			//半径
			ENEMY_COLLIDER_HIGHT,			//高さ
			m_position		//初期座標
		);
	}
	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 拡大率の設定
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// スキンモデルの取得
	/// </summary>
	/// <returns>スキンモデル</returns>
	SkinModel* GetSkinModel()
	{
		return &m_skinModel;
	}
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
	SkinModel m_skinModel;								//スキンモデル。		
	CharacterController m_charaCon;						//キャラクターコントローラー
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_v = CVector3::Zero();					//ベクトル
	CVector3 m_up = CVector3::AxisY();					//上方向
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	float m_gravity = 0.0f;				//重力

	Player* m_player = nullptr;				//プレイヤー
	Game* m_game = nullptr;					//ゲーム
	EnemyBall* m_enemyBall = nullptr;
	
	float m_len = 0.0f;				//距離
	float m_naiseki = 0.0f;			//内積を求める
	float m_angle = 0.0f;			//角度
	int m_timer = 0;				//死亡タイマー　単位：秒
	bool m_isDeath = false;			//死んだ
	CSoundSource m_fumuSE;
};

