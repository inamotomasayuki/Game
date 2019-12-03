#pragma once
#include "physics/PhysicsGhostObject.h"
#include "physics/PhysicsStaticObject.h"
#include "character/CharacterController.h"
class Player;
const float FLOOR_COLLIDER_HIGHT = 0.0f;		//カプセルコライダーの高さ
const float FLOOR_COLLIDER_RADIUS = 0.0f;		//カプセルコライダーの半径

class MoveFloor : public IGameObject
{
public:
	MoveFloor();
	~MoveFloor();
	void Update();
	void Draw();
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		m_charaCon.Init(
			FLOOR_COLLIDER_RADIUS,
			FLOOR_COLLIDER_HIGHT,
			m_position
		);
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
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghostObject;
	}
private:
	/// <summary>
	/// 往復
	/// </summary>
	void RoundTrip();
	SkinModel m_skinModel;							//スキンモデル
	PhysicsStaticObject m_staticObject;				//静的オブジェクト
	PhysicsGhostObject m_ghostObject;				//ゴースト
	CharacterController m_charaCon;					//キャラコン
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度

	Player* m_player = nullptr;			//プレイヤー

	int m_timer = 0;		//タイマー
	float m_speed = 1400.0f;
	enum EnState {
		enState_right,
		enState_left
	};
	EnState m_state;
};

