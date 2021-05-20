#pragma once
#include "physics/PhysicsGhostObject.h"
class Player;
class Game;
class Star final : public IGameObject
{
public:
	Star();
	~Star();
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
	const PhysicsGhostObject* GetGhost() const
	{
		return &m_ghost;
	}
	/// <summary>
	/// 星取得フラグの取得
	/// </summary>
	/// <returns>星取得フラグ</returns>
	bool GetStarFlag() const
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
	int m_timer = 0;						//星取得フラグたてるまでのタイマー　単位：秒
	bool m_getStar = false;					//星取得フラグ
	Player* m_player = nullptr;				//プレイヤー
	Game* m_game = nullptr;					//ゲーム
};

