#pragma once
#include "physics/PhysicsGhostObject.h"
#include "physics/PhysicsStaticObject.h"
#include "sound/SoundSource.h"

namespace {
	const CVector3 GHOST_SCALE = { 50.0f,1.0f,50.0f };		//ゴーストの大きさ
	const float GHOST_UNDER_POS = 50.0f;					//下のゴースト位置
	const float GHOST_UPPER_POS = 30.0f;					//上のゴースト位置
}

class Box final : public IGameObject
{
public:
	Box();
	~Box();
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
		m_ghostPos = pos;
		m_ghostPos.y -= GHOST_UNDER_POS;
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
	/// ゴーストメッシュの取得
	/// </summary>
	/// <returns>ゴーストメッシュ</returns>
	const PhysicsGhostObject* GetMeshGhost() const
	{
		return &m_meshGhostObject;
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
	const CVector3 GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// アイテムの種類
	/// </summary>
	enum EnItem {
		enItem_mikan,		//みかん
		enItem_coin,		//コイン
		enItem_Num			//数
	};
	/// <summary>
	/// アイテム種類設定
	/// </summary>
	/// <param name="item">アイテムの種類</param>
	void SetItem(const EnItem& item)
	{
		m_itemState = item;
	}
	/// <summary>
	/// ヒップドロップされたか設定
	/// </summary>
	/// <param name="hipDrop">フラグ</param>
	void SetIsHipDrop(bool hipDrop) {
		m_isHipDrop = hipDrop;
	}
private:
	SkinModel m_skinModel;								//スキンモデル
	PhysicsStaticObject m_staticObject;					//静的オブジェクト
	PhysicsGhostObject m_ghostObject;					//ゴースト
	PhysicsGhostObject m_meshGhostObject;				//ゴースト
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_ghostPos;								//ゴーストの位置
	CVector3 m_ghostScale = GHOST_SCALE;				//ゴーストの大きさ
	CSoundSource* m_se = nullptr;						//効果音
	EnItem m_itemState;									//アイテムどれ
	bool m_isContact = false;							//ぶつかったかどうか
	bool m_isInitModel = false;							//モデルチェンジしたか
	bool m_isHipDrop = false;							//ヒップドロップされた。
};

