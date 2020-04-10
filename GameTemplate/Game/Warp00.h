#pragma once
#include "Player.h"
#include "Effect.h"
class Warp00 : public IGameObject
{
public:
	Warp00();
	~Warp00();
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
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}

private:
	/// <summary>
	/// 回転
	/// </summary>
	void Rotation();
private:
	SkinModel m_skinModel;		//スキンモデル
	CVector3 m_position;		//位置
	CQuaternion m_rotation;		//回転
	CVector3 m_scale;			//スケール
	Player* m_player = nullptr;		//プレイヤー
	bool m_isWarp = false;			//ワープしたか	
	Effect* m_effect = nullptr;		//エフェクト
};

