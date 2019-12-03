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
			COLLIDER_RADIUS,		//半径
			COLLIDER_HIGHT,			//高さ
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
private:
	CVector3 m_initialPos = CVector3::Zero();			//初期位置
};

