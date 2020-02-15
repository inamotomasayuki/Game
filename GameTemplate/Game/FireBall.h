#pragma once
#include "character/CharacterController.h"

class Player;

class FireBall : public IGameObject
{
public:
	FireBall();
	~FireBall();
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
	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	CVector3 GetPosition()
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
	bool m_isJump = false;		//ジャンプフラグ
	float m_jumpSpeed = 0.0f;	//ジャンプ速度
	int m_deleteTimer = 0;		//削除タイマー　単位：秒
};

