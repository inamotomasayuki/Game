#pragma once
#include "physics/PhysicsGhostObject.h"
#include "physics/PhysicsStaticObject.h"
#include "character/CharacterController.h"
class MoveFloor final : public IGameObject
{
public:
	MoveFloor();
	~MoveFloor();
	/*!
	*@brief 更新
	*/
	void Update() override;
	/*!
	*@brief 描画
	*/
	void Draw() override;
	/*!
	*@brief 初期化
	*/
	void Init();
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/*!
	*@brief キャラコンの初期化
	*@param[in]	pos	座標
	*/
	void InitCharaCon(const CVector3& pos)
	{
		//キャラクターコントローラー
		m_charaCon.Init(
			0.0f,			//半径
			0.0f,			//高さ
			pos								//初期座標
		);
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
	const CVector3& GetPosition() const
	{
		return m_position;
	}

private:
	/// <summary>
	/// 往復
	/// </summary>
	void RoundTrip();
	/*!
	*@brief　EnState
	*　往復ステート
	*/
	enum EnState {
		enState_right,		//行ったり
		enState_left		//来たり
	};
	EnState m_state = enState_right;		//ステート

	SkinModel m_skinModel;							//スキンモデル
	PhysicsStaticObject m_staticObject;				//静的オブジェクト
	PhysicsGhostObject m_ghostObject;				//ゴースト
	CharacterController m_charaCon;					//キャラコン
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	int m_timer = 0;		//タイマー
	bool m_isInit = false;					//初期化した？
};

