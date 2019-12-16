#pragma once
#include "EnemyBase.h"
#include "EnemyBall.h"

class Enemy03 : public EnemyBase
{
public:
	Enemy03();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();
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
private:
	bool m_isAttack = false;		//攻撃したかどうか
	bool m_isAttacked = false;		//攻撃されたかどうか
	int m_waitTimer = 0;			//待機タイマー
	bool m_isChangeModel = false;		//モデルチェンジフラグ
	bool m_isKicked = false;			//蹴られたかどうか
	bool m_isPlayerJump = false;		//プレイヤーが飛んだかどうか
	bool m_isBallAttack = false;		//ボール状態攻撃できるかどうか
	bool m_isApproachAgain = false;		//再々近づいたかどうか

	EnemyBall* m_enemyBall = nullptr;
};

