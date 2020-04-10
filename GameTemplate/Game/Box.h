#pragma once
#include "physics/PhysicsGhostObject.h"
#include "physics/PhysicsStaticObject.h"
#include "Item.h"
#include "sound/SoundSource.h"
class Coin;

const CVector3 GHOST_SCALE = { 50.0f,1.0f,50.0f };		//ゴーストの大きさ
const float GHOST_UNDER_POS = 50.0f;					//下のゴースト位置
const float GHOST_UPPER_POS = 30.0f;					//上のゴースト位置

class Box : public IGameObject
{
public:
	Box();
	~Box();
	void Update();
	void Draw();
	/// <summary>
/// 座標の設定
/// </summary>
/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
		m_ghostPos = pos;
		m_ghostPos.y -= GHOST_UNDER_POS;
		m_ghostMeshPos = pos;
		m_ghostMeshPos.y += GHOST_UPPER_POS;
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
	/// ゴーストの取得
	/// </summary>
	/// <returns>ゴースト</returns>
	PhysicsGhostObject* GetGhostMesh()
	{
		return &m_ghostMesh;
	}

	/// <summary>
	/// ぶつかった設定
	/// </summary>
	/// <param name="contact">ぶつかったかどうか</param>
	void SetIsContact(bool contact)
	{
		m_isContact = contact;
	}
	/// スキンモデルの取得
/// </summary>
/// <returns>スキンモデル</returns>
	SkinModel* GetSkinModel()
	{
		return &m_skinModel;
	}
	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標（位置）</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// ヒップドロップ
	/// </summary>
	void SetIsHipDrop()
	{
		m_isHipDrop = true;
	}
	/// <summary>
	/// ヒップドロップ？
	/// </summary>
	/// <returns></returns>
	bool GetIsHipDrop()
	{
		return m_isHipDrop;
	}
	enum EnItem {
		enItem_mikan,
		enItem_coin,
		enItem_Num
	};
	void SetItem(EnItem item) 
	{
		m_itemState = item;
	}
private:
	SkinModel m_skinModel;								//スキンモデル
	PhysicsStaticObject m_staticObject;					//静的オブジェクト
	PhysicsGhostObject m_ghostObject;					//ゴースト
	PhysicsGhostObject m_ghostMesh;						//ゴーストメッシュ
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_ghostPos;								//ゴーストの位置
	CVector3 m_ghostMeshPos;							//ゴーストの位置
	CVector3 m_ghostScale = GHOST_SCALE;				//ゴーストの大きさ
	bool m_isContact = false;							//ぶつかったかどうか
	bool m_isInitModel = false;							//モデルチェンジしたか
	bool m_isHipDrop = false;							//ヒップドロップ中？
	Item* m_item = nullptr;								//アイテム
	CSoundSource* m_se = nullptr;						//効果音
	EnItem m_itemState;									//アイテムどれ
	Coin* m_coin = nullptr;								//コイン
};

