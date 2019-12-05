#pragma once
#include "character/CharacterController.h"
#include "MoveFloor.h"
#include "Star.h"
class JumpFloor;
class Game;
const float GRAVITY = 400.0f;					//重力
const float COLLIDER_HIGHT = 100.0f;		//カプセルコライダーの高さ
const float COLLIDER_RADIUS = 20.0f;		//カプセルコライダーの半径

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
			COLLIDER_RADIUS,			//半径
			COLLIDER_HIGHT,			//高さ
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
	/// <summary>
	/// ジャンプしてるかどうか
	/// </summary>
	/// <param name="jumpFlag">ジャンプフラグ</param>
	void SetJumpFlag(bool jumpFlag)
	{
		m_jumpFlag = jumpFlag;
		m_jumpSpeed = 4000.0f;
		m_gravity = GRAVITY;
	}
	/// <summary>
	/// 動く床の速度の設定
	/// </summary>
	/// <param name="floorSpeed">動く床の速度</param>
	void SetFloorSpeed(CVector3 floorSpeed)
	{
		m_floorSpeed = floorSpeed;
	}
	/// <summary>
	/// スキンモデルの取得
	/// </summary>
	/// <returns>スキンモデル</returns>
	SkinModel* GetSkinModel()
	{
		return &m_skinModel;
	}
	CVector3 GetMoveSpeed()
	{
		return m_moveSpeed;
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
	/// <summary>
	/// アニメーションクリップのロード
	/// ループフラグ設定
	/// </summary>
	void InitAnimationClip();
	/// <summary>
	/// アニメーションコントローラー
	/// </summary>
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
	Game* m_game = nullptr;							//ゲーム
	Star* m_star = nullptr;							//星

	CVector3 m_floorSpeed = CVector3::Zero();		//床の速度

	enum EnAnimationClip {
		enAnimationClip_idle,	//待機アニメーション。
		enAnimationClip_run,	//走りアニメーション
		enAnimationClip_jump,	//ジャンプアニメーション。
		enAnimationClip_damage,	//ダメージアニメーション
		enAnimationClip_walk,	//歩きアニメーション
		enAnimationClip_down,	//ダウンアニメーション
		enAnimationClip_clear,	//クリアアニメーション
		enAnimationClip_Num		//アニメーションクリップの数。
	};
	AnimationClip m_animClips[enAnimationClip_Num];		//アニメーションクリップ。
	Animation m_animation;								//アニメーション

	bool m_isAttacked = false;		//攻撃を受けてるかどうか
	bool m_jumpFlag = false;		//ジャンプしてるかどうか
	bool m_contactFloor = false;	//床と接触してるかどうか
	bool m_contactJumpFloor = false;	//ジャンプ床と接触してるかどうか
	float m_jumpSpeed;				//ジャンプ速度
	int m_threeStep = 0;			//3段ジャンプカウント
	int m_timer = 0;				//タイマー 単位：秒
	float angle = 0.0f;				//角度
	float m_gravity;				//重力
};