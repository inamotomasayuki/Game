#pragma once
#include "character/CharacterController.h"

class Player;

class FireBall final : public IGameObject
{
public:
	FireBall();
	~FireBall();
	/*!
	*@brief 更新
	*/
	void Update() override;
	/*!
	*@brief 描画
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
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const CVector3& GetPosition() const
	{
		return m_position;
	}
private:
	SkinModel m_skinModel;								//スキンモデル
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_targetPos;								//プレイヤー位置
	CVector3 m_toPos;									//ファイアボールの位置
	CVector3 m_moveSpeed;								//移動速度
	CVector3 m_vectorXZ;								//XZベクトル
	CharacterController m_charaCon;						//キャラクターコントローラー
	Player* m_player = nullptr;							//プレイヤー
	int m_deleteTimer = 0;		//削除タイマー　単位：秒
	float m_jumpSpeed = 0.0f;	//ジャンプ速度
	bool m_isJump = false;		//ジャンプフラグ
};

