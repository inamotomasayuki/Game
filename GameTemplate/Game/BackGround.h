#pragma once
#include "physics/PhysicsStaticObject.h"
#include "physics/PhysicsGhostObject.h"

const float BACK_GHOST_UNDER_POS = 100.0f;		//背景のゴーストの下の位置
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();

	void Update();
	void Draw();
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		m_ghostPos = pos;
		m_ghostPos.y -= BACK_GHOST_UNDER_POS;
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
	/// 静的オブジェクトの取得
	/// </summary>
	/// <returns>静的オブジェクト</returns>
	PhysicsStaticObject* GetPhysicsStaticObject() {
		return &m_physicsStaticObject;
	}
	/// <summary>
	/// ゴーストの取得
	/// </summary>
	/// <returns>ゴースト</returns>
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghostObject;
	}
private:
	SkinModel m_skinModel;								//スキンモデル
	PhysicsGhostObject m_ghostObject;					//ゴースト
	PhysicsStaticObject m_physicsStaticObject;			//静的物理オブジェクト
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_ghostPos;								//ゴーストの位置
};

