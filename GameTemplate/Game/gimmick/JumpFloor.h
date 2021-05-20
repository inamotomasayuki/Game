#pragma once
#include "physics/PhysicsGhostObject.h"
#include "physics/PhysicsStaticObject.h"
#include "../player/Player.h"
class JumpFloor final : public IGameObject
{
public:
	JumpFloor();
	~JumpFloor();
	/*
	* @brief 更新
	*/
	void Update() override;
	/*
	* @brief 描画
	*/
	void Draw() override;
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 拡大率の設定
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// ゴーストの取得
	/// </summary>
	/// <returns>ゴースト</returns>
	const PhysicsGhostObject* GetGhost() const
	{
		return &m_ghostObject;
	}
	/*
	* @brief 座標の取得
	* return 座標 
	*/
	const CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	SkinModel m_skinModel;							//スキンモデル
	PhysicsStaticObject m_staticObject;				//静的オブジェクト
	PhysicsGhostObject m_ghostObject;				//ゴースト
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
};

