#pragma once
#include "physics/PhysicsGhostObject.h"
#include "physics/PhysicsStaticObject.h"
#include "Item.h"

class Box : public IGameObject
{
public:
	Box();
	~Box();
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
		m_ghostPos.y -= 50.0f;
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
/// ゴーストの取得
/// </summary>
/// <returns>ゴースト</returns>
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghostObject;
	}
	void SetIsContact(bool contact)
	{
		m_isContact = contact;
	}
	/// スキンモデルの取得
/// </summary>
/// <returns>スキンモデル</returns>
	SkinModel* GetSkinModel()
	{
		return &m_skinModel;
	}

private:
	SkinModel m_skinModel;							//スキンモデル
	PhysicsStaticObject m_staticObject;				//静的オブジェクト
	PhysicsGhostObject m_ghostObject;				//ゴースト
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_ghostPos;
	CVector3 m_ghostScale = { 50.0f,1.0f,50.0f };
	bool m_isContact = false;
	bool m_isInitModel = false;
	int m_timer = 0;									//タイマー　単位：秒
	
	Item* m_item = nullptr;
};

