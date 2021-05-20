#pragma once
#include "physics/PhysicsGhostObject.h"
#include "sound/SoundSource.h"
namespace {
	const float ITEM_END_POS_UP = 80.0f;				//アイテム最終位置
	const float ITEM_END_POS_DOWN = 120.0f;				//アイテム最終位置
}
class Item final : public IGameObject
{
public:
	Item();
	~Item();
	void Update() override;
	void Draw() override;
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
		m_posUp = m_position.y + ITEM_END_POS_UP;
		m_posDown = m_position.y - ITEM_END_POS_DOWN;
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
	/// <summary>
	/// 取得したを設定
	/// </summary>
	void SetIsGet()
	{
		m_isGet = true;
	}
	/// <summary>
	/// ヒップドロップされた。
	/// </summary>
	void IsHipDrop()
	{
		m_isHipDrop = true;
	}
private:
	/// <summary>
	/// 回転
	/// </summary>
	void Rotation();
private:
	SkinModel m_skinModel;							//スキンモデル
	PhysicsGhostObject m_ghostObject;				//ゴースト
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CSoundSource* m_se = nullptr;						//効果音
	CVector3 m_boxPos;									//箱の位置
	float m_posUp = 0.0f;								//上がる位置
	float m_posDown = 0.0f;								//下がる位置	
	bool m_isGet = false;								//取得されたか
	bool m_isHipDrop = false;							//ヒップドロップされたか
	bool m_isInit = false;								//ゴースト初期化
};	

