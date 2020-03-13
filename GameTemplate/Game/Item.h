#pragma once
#include "physics/PhysicsGhostObject.h"
#include "character/CharacterController.h"
#include "sound/SoundSource.h"
class Player;
class Box;
const float ITEM_COLLIDER_RADIUS = 5.0f;
const float ITEM_COLLIDER_HIGHT = 5.0f;

class Item : public IGameObject
{
public:
	Item();
	~Item();
	void Update();
	void Draw();
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		//キャラクターコントローラー
		m_charaCon.Init(
			ITEM_COLLIDER_RADIUS,			//半径
			ITEM_COLLIDER_HIGHT,			//高さ
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
/// ゴーストの取得
/// </summary>
/// <returns>ゴースト</returns>
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghostObject;
	}
	/// <summary>
	/// 取得したを設定
	/// </summary>
	void SetIsGet()
	{
		m_isGet = true;
	}
private:
	/// <summary>
	/// 回転
	/// </summary>
	void Rotation();
private:
	SkinModel m_skinModel;							//スキンモデル
	PhysicsGhostObject m_ghostObject;				//ゴースト
	CharacterController m_charaCon;					//キャラコン
	CVector3 m_moveSpeed;							//移動速度
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	bool m_isGet = false;								//取得されたか
	CSoundSource m_se;									//効果音
	Player* m_player = nullptr;							//プレイヤー
	CVector3 m_boxPos;									//箱の位置
	float m_posUp = 0.0f;								//上がる位置
	bool m_isHipDrop = false;							//ヒップドロップ中か
};	

