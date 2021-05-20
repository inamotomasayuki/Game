#pragma once
#include "EnemyBase.h"
class Enemy01 final : public EnemyBase
{
public:
	Enemy01();
	void Update() override;
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
		//初期位置
		m_initialPos = pos;
	}
private:
	/// <summary>
	/// 追跡
	/// </summary>
	void Search();
	/// <summary>
	/// 初期位置に戻る
	/// </summary>
	void Return();
	/// <summary>
	/// 回転
	/// </summary>
	void Rotation() override;
	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack() override;
	/// <summary>
	///	死亡
	/// </summary>
	/// <param name="score">スコア</param>
	void Death(int score) override;

private:
	CVector3 m_initialPos = CVector3::Zero();	//初期位置	
	int m_waitTimer = 0;						//待機タイマー
	bool m_isAttack = false;					//攻撃したかどうか
	bool m_isAttacked = false;					//攻撃されたかどうか
};