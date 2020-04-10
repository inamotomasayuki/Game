#pragma once
#include "EnemyBase.h"
const float ENEMYBALL_COLLIDER_RADIUS = 28.0f;		//カプセルコライダーの半径
const float ENEMYBALL_COLLIDER_HIGHT = 80.0f;		//カプセルコライダーの高さ

class EnemyBall : public EnemyBase
{
public:
	EnemyBall();
	void Update();
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		//キャラクターコントローラー
		m_charaCon.Init(
			ENEMYBALL_COLLIDER_RADIUS,			//半径
			ENEMYBALL_COLLIDER_HIGHT,			//高さ
			m_position		//初期座標
		);
	}
	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	CVector3 GetPositon()
	{
		return m_position;
	}
	/// <summary>
	/// 蹴られてるかどうか
	/// </summary>
	/// <returns>蹴られたか</returns>
	bool GetIsKicked()
	{
		return m_isKicked;
	}
private:
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
	/// 回転
	/// </summary>
	void Rotation();
	/// <summary>
	/// 玉状態
	/// </summary>
	void Ball();
private:
	bool m_isAttack = false;		//攻撃したかどうか
	bool m_isAttacked = false;		//攻撃されたかどうか
	int m_waitTimer = 0;			//待機タイマー
	bool m_isChangeModel = false;		//モデルチェンジフラグ
	bool m_isKicked = false;			//蹴られたかどうか
	bool m_isPlayerJump = false;		//プレイヤーが飛んだかどうか
	bool m_isBallAttack = false;		//ボール状態攻撃できるかどうか
	bool m_isApproachAgain = false;		//再々近づいたかどうか
	CSoundSource* m_pokoSE = nullptr;
};

