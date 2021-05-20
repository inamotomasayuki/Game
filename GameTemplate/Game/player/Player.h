#pragma once
#include "character/CharacterController.h"
#include "../gimmick/MoveFloor.h"
#include "../item/Star.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "../stage/BackGround.h"
#include "PlayerWarpState.h"

class JumpFloor;
class Game;

namespace {
	const float GRAVITY = 400.0f;					//重力
	const float PLAYER_COLLIDER_HIGHT = 100.0f;		//カプセルコライダーの高さ
	const float PLAYER_COLLIDER_RADIUS = 10.0f;		//カプセルコライダーの半径
}
class Player final : public IGameObject
{
public:
	Player();
	~Player();
	/*
	* @brieef 更新
	*/
	void Update() override;
	/*
	* @brieef 描画
	*/
	void Draw() override;
	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const CVector3& GetPositon() const
	{
		return m_position;
	}
	/// <summary>
	/// 回転の取得
	/// </summary>
	/// <returns></returns>
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}
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
			PLAYER_COLLIDER_RADIUS,			//半径
			PLAYER_COLLIDER_HIGHT,			//高さ
			pos								//初期座標
		);
	}
	/// <summary>
	/// キャラコン座標設定
	/// </summary>
	/// <param name="v">座標</param>
	void SetCharaConPos(CVector3 v)
	{
		m_charaCon.SetPosition(v);
		m_position = m_charaCon.GetPosition();
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
	/// 加速度の設定
	/// </summary>
	/// <param name="addSpeed">加速度</param>
	void SetAddSpeed(const CVector3& addSpeed)
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
	bool GetIsAttacked() const
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
		m_se[enSE_jump]->Play(false);
	}
	/// <summary>
	/// 動く床の速度の設定
	/// </summary>
	/// <param name="floorSpeed">動く床の速度</param>
	void SetFloorSpeed(const CVector3& floorSpeed)
	{
		m_floorSpeed = floorSpeed;
	}
	/// <summary>
	/// スキンモデルの取得
	/// </summary>
	/// <returns>スキンモデル</returns>
	SkinModel* GetSkinModel()
	{
		return &m_skinModelCircle;
	}
	/// <summary>
	/// 移動速度の取得
	/// </summary>
	/// <returns>移動速度</returns>
	const CVector3& GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
	/// <summary>
	/// ヒップドロップ中
	/// </summary>
	/// <returns></returns>
	bool IsHipDrop() const
	{
		return m_isHipDrop;
	}
	/// <summary>
	/// ダメージ音を鳴らしたか設定
	/// </summary>
	/// <param name="SE">鳴らしたか</param>
	void SetIsDamageSE(bool SE)
	{
		m_isDamageSE = SE;
	}
	/// <summary>
	/// アイテム取得？
	/// </summary>
	/// <returns>フラグ</returns>
	bool GetisItem() const
	{
		return m_isItem;
	}
	/// <summary>
	/// ボタンステート
	/// </summary>
	enum EnButtonState {
		enButtonState_0,	//ボタン０
		enButtonState_1,	//ボタン１
		enButtonState_Num	//数
	};
	/// <summary>
	/// ボタンステート取得
	/// </summary>
	/// <returns>ボタンステート</returns>
	int GetButtonState() const
	{
		return m_buttonState;
	}
	/// <summary>
	/// ボタン押してない設定
	/// </summary>
	void SetIsButtonFalse()
	{
		m_isButton = false;
	}
	/// <summary>
	/// 地面にいるか
	/// </summary>
	/// <returns>地面にいるか</returns>
	bool IsOnGround() const
	{
		if (m_charaCon.IsOnGround()) {
			return true;
		}
		else {
			return false;
		}
	}
	/// <summary>
	/// ボックスヒップドロップしたか
	/// </summary>
	bool IsHipDropBox() const
	{
		return m_isHipDropBox;
	}
	/// <summary>
	/// あちちダメージ受けた
	/// </summary>
	void SetIsAchichi()
	{
		m_jumpSpeed = 3500.0f;
		m_jumpFlag = true;
		m_isAchichi = true;
	}
	/// <summary>
	/// あちちちベクトル
	/// </summary>
	/// <param name="vec">ベクトル</param>
	void SetAchichiVec(const CVector3& vec)
	{
		m_achichiVec = vec;
	}
protected:
	bool IsInputJump() const
	{
		return g_pad[0].IsTrigger(enButtonA);
	}
	bool IsInputDash() const
	{
		return g_pad[0].IsPress(enButtonB);
	}
	bool IsInputFireBall() const
	{
		return g_pad[0].IsTrigger(enButtonRB1);
	}
	bool IsInputHipDrop() const
	{
		return g_pad[0].IsTrigger(enButtonRB2);
	}
	bool IsInputMenu() const
	{
		return g_pad[0].IsTrigger(enButtonStart);
	}
	float GetInputLStickXF() const
	{
		return g_pad[0].GetLStickXF();
	}
	float GetInputLStickYF() const
	{
		return g_pad[0].GetLStickYF();
	}
private:
	void Playing();
	void HipDrop();
	void Damage();
	void FireDamage();
	void GameClear();
	void GameOver();
	/// <summary>
	/// カメラを考慮したスティックでの移動
	/// </summary>
	void PadMove();
	/// <summary>
	/// プレイヤーの回転
	/// </summary>
	//void Rotation();
	/// <summary>
	/// ファイアボール生成
	/// </summary>
	void FireBallGenerate();
	/// <summary>
	/// アニメーションクリップのロード
	/// ループフラグ設定
	/// </summary>
	void InitAnimationClip();
	/// <summary>
	/// アニメーションコントローラー
	/// </summary>
	//void AnimationController();
	/// <summary>
	/// プレイヤーと他のゴーストとの接触処理
	/// </summary>
	void GhostContact();
	/// <summary>
	/// サウンドの初期化
	/// </summary>
	void InitSound();
	/// <summary>
	/// サウンド再生
	/// </summary>
	void SoundPlay();
private:
	SkinModel m_skinModel;								//スキンモデル。
	SkinModel m_skinModelCircle;						//円用スキンモデル
	CharacterController m_charaCon;						//キャラクターコントローラー
	CVector3 m_position = CVector3::Zero();				//位置
	CVector3 m_circlePos = CVector3::Zero();			//円の位置
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	CVector3 m_addSpeed = CVector3::Zero();				//加速度
	CQuaternion m_jumpRot = CQuaternion::Identity();	//3段ジャンプ目の回転
	CVector3 m_posXZ;									//XZベクトル
	CVector3 m_floorSpeed = CVector3::Zero();			//床の速度
	CVector3 m_achichiVec;								//あちちちベクトル
	CVector3 m_achichiMove = CVector3::Zero();			//あちちち移動
	JumpFloor* m_jumpFloor = nullptr;				//ジャンプ床
	MoveFloor* m_moveFloor = nullptr;				//動く床
	BackGround* m_backGround = nullptr;				//背景
	Game* m_game = nullptr;							//ゲーム
	Star* m_star = nullptr;							//星
	PlayerWarpState m_playerWarpState;
	enum EnState {
		enState_Playing,
		enState_HipDrop,
		enState_GetStar,
		enState_Damage,
		enState_FireDamage,
		enState_GameClear,
		enState_GameOver,
		enState_Warp
	};
	EnState m_currentState = enState_Playing;
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
	enum EnSE {
		enSE_jump,		//ジャンプ音
		enSE_jumpFloor,	//ジャンプ床音
		enSE_walk,		//歩行音
		enSE_dash,		//ダッシュ音
		enSE_damage,	//ダメージ音
		enSE_kyodaika,	//巨大化
		enSE_awawaVoice,//あわわわ
		enSE_Num		//SEの数
	};
	CSoundSource* m_se[enSE_Num];	//効果音[SEの数分]	
private:
	int m_fireBallTimer = 0;		//ファイアボール生成タイマー
	int m_flashingTimer = 0;		//点滅タイマー
	int m_threeStep = 0;			//3段ジャンプカウント
	int m_timer = 0;				//タイマー 単位：秒
	int m_hipDropTimer = 0;			//ヒップドロップ
	int m_threeStepRotTimer = 0;	//三段目ジャンプ回転
	int m_buttonState = 0;			//ボタンステート
	int m_waitTimer = 0;			//攻撃された時の待ち時間
	int m_achichiTimer = 0;			//あちち時間
	float m_jumpSpeed;				//ジャンプ速度
	float m_rotSpeed = 0.0f;		//回転速度
	float angle = 0.0f;				//角度
	float m_gravity = 0.0f;			//重力
	bool m_isAttacked = false;		//攻撃を受けてるかどうか
	bool m_jumpFlag = false;		//ジャンプしてるかどうか
	bool m_contactFloor = false;	//床と接触してるかどうか
	bool m_contactJumpFloor = false;//ジャンプ床と接触してるかどうか
	bool m_isHipDrop = false;		//ヒップドロップ中
	bool m_isDamageSE = false;		//ダメージ音ならしたか
	bool m_hitBox = false;			//箱にぶつかったか
	bool m_isItem = false;			//アイテム取ったか
	bool m_isSetGravity = false;	//重力
	bool m_isBigSE = false;			//巨大化SE
	bool m_isFireBall = false;		//ファイアボール生成中？
	bool m_isFlashing = false;		//点滅フラグ
	bool m_isButton = false;		//ボタン押してるか
	//bool m_isFall = false;			//落ちてるか
	bool m_isHipDropBox = false;	//ボックスをヒップドロップしたか
	bool m_isThreeStepRot = false;	//３段目ジャンプの回転
	bool m_isAchichi = false;		//あちち？
	bool m_isVoicePlay = false;		//あちち声再生された？	
	bool m_isInitGravity = false;
};
