#pragma once
#include "physics/PhysicsGhostObject.h"
class Player;
class Game;
class Star : public IGameObject
{
public:
	Star();
	~Star();
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
	/// <summary>
	/// ゴーストの取得
	/// </summary>
	/// <returns></returns>
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghost;
	}
	bool GetStarFlag()
	{
		return m_getStar;
	}
private:
	/// <summary>
	/// 回転
	/// </summary>
	void Rotation();
private:
	SkinModel m_skinModel;									//スキンモデル
	PhysicsGhostObject m_ghost;								//ゴースト
	CVector3 m_position = CVector3::Zero();					//座標
	CQuaternion m_rotation = CQuaternion::Identity();		//回転
	CVector3 m_scale = CVector3::One();						//拡大率。
	int m_timer = 0;
	bool m_getStar = false;
	Player* m_player = nullptr;				//プレイヤー
	Game* m_game = nullptr;
};

