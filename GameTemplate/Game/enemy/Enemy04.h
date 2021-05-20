#pragma once
#include "EnemyBase.h"
class Enemy04 final : public EnemyBase
{
public:
	Enemy04();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update() override;
private:
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
	/// <summary>
	/// ファイアボール生成
	/// </summary>
	void FireBallGenerate();
private:
	CSoundSource* m_fireSE = nullptr;	//効果音
	int m_waitTimer = 0;			//待機タイマー
	int m_fireGenerateTimer = 0;	//ファイアボール生成タイマー
	bool m_isFireBallGenerate = false;	//ファイアボール生成したか。
	bool m_isAttack = false;		//攻撃したかどうか
	bool m_isAttacked = false;		//攻撃されたかどうか
};