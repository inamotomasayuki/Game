#pragma once
#include "character/CharacterController.h"
#include "MoveFloor.h"
#include "JumpFloor.h"
#include "BackGround.h"
class JumpFloor;
class Player : public IGameObject
{
public:
	Player();
	~Player();

	void Update();
	void Draw();
	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	CVector3 GetPositon()
	{
		return m_position;
	}
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		//キャラクターコントローラー
		m_charaCon.Init(
			20.0,			//半径
			100.0f,			//高さ
			m_position		//初期座標
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
	/// <summary>
	/// 加速度の設定
	/// </summary>
	/// <param name="addSpeed">加速度</param>
	void SetAddSpeed(CVector3 addSpeed)
	{
		m_addSpeed = addSpeed;
	}
	/// <summary>
	/// 攻撃を受けてるかどうか。
	/// </summary>
	/// <param name="isAttacked">フラグ</param>
	void SetIsAttacked(bool isAttacked) 
	{
		m_isAttacked = isAttacked;
	}
	/// <summary>
	/// 攻撃を受けてるかどうかを取得
	/// </summary>
	/// <returns>攻撃を受けてるかどうかのフラグ</returns>
	bool GetIsAttacked()
	{
		return m_isAttacked;
	}
	void SetJumpFlag(bool jumpFlag)
	{
		m_jumpFlag = jumpFlag;
		m_jumpSpeed = 5000.0f;
	}
	void SetFloorSpeed(CVector3 floorSpeed)
	{
		m_floorSpeed = floorSpeed;
	}
	SkinModel* GetSkinModel()
	{
		return &m_skinModel;
	}

private:
	/// <summary>
	/// カメラを考慮したスティックでの移動
	/// </summary>
	void PadMove();
	/// <summary>
	/// プレイヤーの回転
	/// </summary>
	void Rotation();
	void AnimationController();
private:
	SkinModel m_skinModel;								//スキンモデル。
	CharacterController m_charaCon;						//キャラクターコントローラー
	CVector3 m_position = CVector3::Zero();				//位置
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	CVector3 m_addSpeed = CVector3::Zero();				//加速度
	CQuaternion m_jumpRot = CQuaternion::Identity();	//3段ジャンプ目の回転

	JumpFloor* m_jumpFloor = nullptr;				//ジャンプ床
	MoveFloor* m_moveFloor = nullptr;				//動く床
	BackGround* m_backGround = nullptr;

	CVector3 m_floorSpeed = CVector3::Zero();		//床の速度

	enum EnAnimationClip {
		enAnimationClip_idle,	//待機アニメーション。
		enAnimationClip_run,	//走りアニメーション
		enAnimationClip_jump,	//ジャンプアニメーション。
		enAnimationClip_damage,
		enAnimationClip_walk,
		enAnimationClip_Num		//アニメーションクリップの数。
	};
	AnimationClip m_animClips[enAnimationClip_Num];		//アニメーションクリップ。
	Animation m_animation;								//アニメーション

	bool m_isAttacked = false;		//攻撃を受けてるかどうか
	bool m_jumpFlag = false;		//ジャンプしてるかどうか
	bool m_contactFloor = false;	//床と接触してるかどうか
	bool m_contactJumpFloor = false;
	float m_jumpSpeed;				//ジャンプ速度
	int m_threeStep = 0;			//3段ジャンプカウント
	int m_timer = 0;				//タイマー
	float angle = 0.0f;				//角度
};