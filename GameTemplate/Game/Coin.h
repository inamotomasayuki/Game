#pragma once
#include "Player.h"

class Game;
class Coin : public IGameObject
{
public:
	Coin();
	~Coin();
	void Update();
	void Draw();
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 拡大率の設定
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}
	/// <summary>
/// スキンモデルの取得
/// </summary>
/// <returns>スキンモデル</returns>
	SkinModel* GetSkinModel()
	{
		return &m_skinModel;
	}

private:
	/// <summary>
	/// 回転
	/// </summary>
	void Rotation();
	/// <summary>
	/// コインを獲得
	/// </summary>
	void GetCoin();
private:
	SkinModel m_skinModel;				//スキンモデル。
	CVector3 m_position = CVector3::Zero();					//座標
	CQuaternion m_rotation = CQuaternion::Identity();		//回転
	CVector3 m_scale = CVector3::One();						//拡大率。
	CVector3 m_moveSpeed = CVector3::Zero();				//移動速度

	Player* m_player = nullptr;				//プレイヤー
	Game* m_game = nullptr;					//ゲーム

	int m_timer = 0;						//タイマー
	bool m_coinGetFlag = false;				//コイン取得フラグ
};

