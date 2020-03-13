#pragma once
#include "EnemyBase.h"
class Enemy01 : public EnemyBase
{
public:
	Enemy01();
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
			ENEMY_COLLIDER_RADIUS,		//半径
			ENEMY_COLLIDER_HIGHT,			//高さ
			m_position		//初期座標
		);
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
	void Rotation();
	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();
	/// <summary>
	///	死亡
	/// </summary>
	/// <param name="score">スコア</param>
	void Death(int score);

private:
	CVector3 m_initialPos = CVector3::Zero();			//初期位置
	bool m_isAttack = false;		//攻撃したかどうか
	bool m_isAttacked = false;		//攻撃されたかどうか
	int m_waitTimer = 0;			//待機タイマー

};

