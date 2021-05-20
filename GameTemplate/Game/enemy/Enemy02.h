#pragma once
#include "EnemyBase.h"
class Enemy02 final : public EnemyBase
{
public:
	Enemy02();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update() override;
private:
	/// <summary>
	/// 移動
	/// </summary>
	void Move();
	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack() override;
	/// <summary>
	///	死亡
	/// </summary>
	/// <param name="score">スコア</param>
	void Death(int score) override;
	/// <summary>
	/// 回転
	/// </summary>
	void Rotation() override;
	int m_waitTimer = 0;			//待機タイマー
	int m_timer = 0;				//往復用タイマー　単位：秒
	float m_jumpSpeed = 0.0f;		//ジャンプ速度
	bool m_isAttack = false;		//攻撃したかどうか
	bool m_isAttacked = false;		//攻撃されたかどうか
	bool m_isJump = false;			//ジャンプフラグ
	/*!
	*@brief EnState
	*　往復ステート
	*/
	enum EnState {
		enState_right,		//行ったり
		enState_left,		//来たり
		enState_Num			//数
	};
	EnState m_state;		//ステート
};