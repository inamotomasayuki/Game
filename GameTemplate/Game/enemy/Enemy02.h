#pragma once
#include "EnemyBase.h"
class Enemy02 : public EnemyBase
{
public:
	Enemy02();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();
private:
	/// <summary>
	/// 移動
	/// </summary>
	void Move();
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

	bool m_isAttack = false;		//攻撃したかどうか
	bool m_isAttacked = false;		//攻撃されたかどうか
	int m_waitTimer = 0;			//待機タイマー
	int m_rand = 0;					//乱数
	bool m_isJump = false;		//ジャンプフラグ
	float m_jumpSpeed = 0.0f;	//ジャンプ速度
	int m_timer = 0;			//往復用タイマー　単位：秒
	enum EnState {
		enState_right,		//行ったり
		enState_left		//来たり
	};
	EnState m_state;		//ステート
};