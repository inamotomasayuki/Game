#pragma once
#include "physics/PhysicsStaticObject.h"
#include "physics/PhysicsGhostObject.h"
#include "sound/SoundSource.h"
#include "GameTime.h"
#include "Font.h"
class Game;
class Button : public IGameObject
{
public:
	Button();
	~Button();
	void Update();
	void Draw();
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		m_initPos = pos;
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
	/// ゴーストの取得
	/// </summary>
	/// <returns>ゴースト</returns>
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghostObject;
	}
	/// <summary>
	/// 時間の取得
	/// </summary>
	/// <returns></returns>
	float GetTimer()
	{
		return m_timer;
	}
	void IsPush()
	{
		m_isPush = true;
	}
	bool GetIsPush()
	{
		return m_isPush;
	}
	enum EnState
	{
		enState_0,
		enState_1,
		enState_stop,
		enState_Num
	};
	void SetState(EnState state)
	{
		m_state = state;
	}
	EnState GetState()
	{
		return m_state;
	}
private:
	SkinModel m_skinModel;								//スキンモデル
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_movePos = m_position;				//移動位置
	CVector3 m_initPos = CVector3::Zero();				//初期座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CSoundSource* m_fumuSE = nullptr;					//効果音
	PhysicsGhostObject m_ghostObject;					//ゴースト
	PhysicsStaticObject m_physicsStaticObject;			//静的物理オブジェクト
	Font m_font;										//フォント
	Game* m_game = nullptr;
	EnState m_state;
	bool m_isSE = false;								//効果音なった？
	bool m_isDown = false;								//下がった？
	bool m_isPush = false;
	bool m_isDelete = false;
	float m_timer = 11.0f;								//タイマー
};

