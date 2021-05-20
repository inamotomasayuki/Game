#pragma once
#include "physics/PhysicsStaticObject.h"
#include "physics/PhysicsGhostObject.h"
#include "sound/SoundSource.h"
#include "../time/GameTime.h"
#include "../graphics/2D/Font.h"
class Game;
namespace {
	const float LIMIT_TIMER = 11.0f;			//制限時間
	const float GHOST_UP_POS_Y = 50.0f;			//ゴーストの位置を上げる
}
class Button final: public IGameObject
{
public:
	Button();
	~Button();
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
		//座標
		m_position = pos;
		//初期座標
		m_initPos = pos;
		//ゴースト座標
		m_ghostPos = pos;
		m_ghostPos.y += GHOST_UP_POS_Y;
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
	/// 時間の取得
	/// </summary>
	/// <returns></returns>
	float GetTimer() const
	{
		return m_timer;
	}
	/// <summary>
	/// 押した設定
	/// </summary>
	void IsPush()
	{
		m_isPush = true;
	}
	/*!
	* @brief 押したかフラグを返す
	* @return フラグ
	*/
	bool GetIsPush()
	{
		return m_isPush;
	}
	/*!
	* @enum EnState
	* ボタンの種類
	*/
	enum EnState
	{
		enState_0,		//ボタン０
		enState_1,		//ボタン１
		enState_2,		//ボタン２
		enState_stop,	//止める
		enState_Num		//数
	};
	/*!
	* @brief　ボタン種類の設定
	* @param state ボタンの種類
	*/
	void SetState(const EnState& state)
	{
		m_state = state;
	}
	/*!
	* @brief ボタンの種類の状態を返す
	* @return ボタンの種類の状態
	*/
	const EnState& GetState() const
	{
		return m_state;
	}
private:
	SkinModel m_skinModel;								//スキンモデル
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_movePos = m_position;				//移動位置
	CVector3 m_ghostPos = CVector3::Zero();				//初期座標

	CVector3 m_initPos = CVector3::Zero();				//初期座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CSoundSource* m_fumuSE = nullptr;					//効果音
	PhysicsGhostObject m_ghostObject;					//ゴースト
	PhysicsStaticObject m_physicsStaticObject;			//静的物理オブジェクト
	Font m_font;										//フォント
	Game* m_game = nullptr;								//ゲーム
	EnState m_state;									//ボタンステート
	
	float m_timer = LIMIT_TIMER;								//タイマー
	bool m_isSE = false;								//効果音なった？
	bool m_isDown = false;								//下がった？
	bool m_isPush = false;								//押した？
	bool m_isDelete = false;							//削除した？
	bool m_isInit = false;								//初期化した？
};

