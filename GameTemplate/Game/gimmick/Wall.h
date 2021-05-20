#pragma once
#include "physics/PhysicsStaticObject.h"
#include "Button.h"
class Wall final : public IGameObject
{
public:
	Wall();
	~Wall();
	/*!
	* @brief 更新
	*/
	void Update() override;
	/*!
	* @brief 描画
	*/
	void Draw() override;
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
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
private:
	SkinModel m_skinModel;								//スキンモデル
	CVector3 m_position = { 300.0f,0.0f,0.0f };			//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	PhysicsStaticObject m_physicsStaticObject;			//静的物理オブジェクト
	bool m_isInit = false;								//初期化した？
};

