#pragma once
#include "Player.h"
class Game;
class EnemyBase : public IGameObject
{
public:
	~EnemyBase() {};
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
			COLLIDER_RADIUS,			//半径
			COLLIDER_HIGHT,			//高さ
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
	SkinModel* GetSkinModel()
	{
		return &m_skinModel;
	}
protected:
	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();
	/// <summary>
	///	死亡
	/// </summary>
	/// <param name="score">スコア</param>
	void Death(int score);
	/// <summary>
	/// プレイヤーに伸びるベクトル&正規化    
	/// </summary>
	void VectorToPlayer()
	{
		m_v = m_player->GetPositon() - m_position;
		m_len = m_v.Length();
		m_v.Normalize();
	}
	void Angle()
	{
		m_naiseki = m_v.Dot(m_up);
		m_angle = acos(m_naiseki);
	}

	SkinModel m_skinModel;								//スキンモデル。		
	CharacterController m_charaCon;						//キャラクターコントローラー
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	CVector3 m_v = CVector3::Zero();					//ベクトル
	CVector3 m_up = CVector3::AxisY();					//上方向

	Player* m_player = nullptr;				//プレイヤー
	Game* m_game = nullptr;					//ゲーム

	bool m_isAttack = false;		//攻撃したかどうか
	bool m_isAttacked = false;		//攻撃されたかどうか
	int m_waitTimer = 0;			//待機タイマー
	float m_len = 0.0f;				//距離
	float m_naiseki = 0.0f;			//内積を求める
	float m_angle = 0.0f;			//角度
};

