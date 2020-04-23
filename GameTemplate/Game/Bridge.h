#pragma once
#include "Button.h"
#include "physics/PhysicsStaticObject.h"
class Bridge : public IGameObject
{
public:
	Bridge();
	~Bridge();

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
private:
	SkinModel m_skinModel;								//スキンモデル
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	PhysicsStaticObject m_physicsStaticObject;			//静的物理オブジェクト
	bool m_isCreatePhysics = false;						//静的物理オブジェクト作成？
};

