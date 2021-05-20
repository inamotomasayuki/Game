#pragma once
#include "EnemyBase.h"
class EnemyBall final : public EnemyBase
{
public:
	EnemyBall();
	void Update() override;
	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const CVector3& GetPositon() const
	{
		return m_position;
	}
	/// <summary>
	/// 蹴られてるかどうか
	/// </summary>
	/// <returns>蹴られたか</returns>
	bool GetIsKicked() const
	{
		return m_isKicked;
	}
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
	/// 玉状態
	/// </summary>
	void Ball();
private:
	CSoundSource* m_pokoSE = nullptr;	//効果音
	int m_waitTimer = 0;			//待機タイマー
	int m_deleteTimer = 0;			//削除タイマー
	bool m_isAttack = false;		//攻撃したかどうか
	bool m_isAttacked = false;		//攻撃されたかどうか
	bool m_isChangeModel = false;		//モデルチェンジフラグ
	bool m_isKicked = false;			//蹴られたかどうか
	bool m_isPlayerJump = false;		//プレイヤーが飛んだかどうか
	bool m_isBallAttack = false;		//ボール状態攻撃できるかどうか
	bool m_isApproachAgain = false;		//再々近づいたかどうか
};

