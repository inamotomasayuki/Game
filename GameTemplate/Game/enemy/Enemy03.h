#pragma once
#include "EnemyBase.h"
#include "EnemyBall.h"

const float PASS_POS = 200.0f;		//パスの位置、

struct Point {
	CVector3 s_position;		//ポイントの座標
	int s_number;				//ポイントの番号
};
class Enemy03 : public EnemyBase
{
public:
	Enemy03();
	/// <summary>
	/// 更新関数
	/// </summary>
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
			ENEMY_COLLIDER_RADIUS,			//半径
			ENEMY_COLLIDER_HIGHT,			//高さ
			m_position		//初期座標
		);
		m_pointList.push_back({ CVector3(m_position.x,m_position.y,m_position.z),1 });				//1番目のポイント
		m_pointList.push_back({ CVector3(m_position.x + PASS_POS,m_position.y,m_position.z),2 });   //2番目のポイント
		m_pointList.push_back({ CVector3(m_position.x,m_position.y,m_position.z + PASS_POS),3 });   //3番目のポイント
		m_point = &m_pointList[0];                              //一番目のポイントを入れる
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
	/// パス移動
	/// </summary>
	void PassMove();
private:
	bool m_isAttack = false;		//攻撃したかどうか
	bool m_isAttacked = false;		//攻撃されたかどうか
	int m_waitTimer = 0;			//待機タイマー
	bool m_isChangeModel = false;		//モデルチェンジフラグ
	bool m_isKicked = false;			//蹴られたかどうか
	bool m_isPlayerJump = false;		//プレイヤーが飛んだかどうか
	bool m_isBallAttack = false;		//ボール状態攻撃できるかどうか
	bool m_isApproachAgain = false;		//再々近づいたかどうか
	bool m_isHipDrop = false;			//ヒップドロップかどうか
	EnemyBall* m_enemyBall = nullptr;	//敵（甲羅）
	std::vector<Point> m_pointList;		//ポイントリスト
	Point* m_point;						//ポイント
};

