#pragma once
#include "../player/Player.h"
#include "../enemy/EnemyBall.h"
#include "physics/PhysicsGhostObject.h"
#include "sound/SoundSource.h"
class Game;
class Coin final : public IGameObject
{
public:
	Coin();
	~Coin();
	/*!
	* @brief 更新
	*/
	void Update() override;
	/*!
	* @brief 描画
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
	/// <returns>座標</returns>
	const CVector3& GetPositon() const
	{
		return m_position;
	}
	/// <summary>
	/// コイン取った
	/// </summary>
	void SetCoinGet()
	{
		m_coinGetFlag = true;
	}
private:
	/// <summary>
	/// 回転
	/// </summary>
	void Rotation();
	/// <summary>
	/// コインを獲得
	/// </summary>
	void GetCoin();
private:
	SkinModel m_skinModel;				//スキンモデル。
	PhysicsGhostObject m_ghostObject;				//ゴースト

	CVector3 m_position = CVector3::Zero();					//座標
	CQuaternion m_rotation = CQuaternion::Identity();		//回転
	CQuaternion m_addRot = CQuaternion::Identity();			//加算回転
	CVector3 m_scale = CVector3::One();						//拡大率。
	CVector3 m_moveSpeed = CVector3::Zero();				//移動速度

	Player* m_player = nullptr;				//プレイヤー
	Game* m_game = nullptr;					//ゲーム
	EnemyBall* m_enemyBall = nullptr;		//敵玉
	int m_timer = 0;						//タイマー
	bool m_coinGetFlag = false;				//コイン取得フラグ
	CSoundSource* m_se = nullptr;			//効果音
	bool m_isInit = false;					//回転初期化
};

