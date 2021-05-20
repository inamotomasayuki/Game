#pragma once
#include "../player/Player.h"
class EnemyFireBall final : public IGameObject
{
public:
	EnemyFireBall();
	~EnemyFireBall();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ベクトルの設定
	/// </summary>
	/// <param name="vec">ベクトル</param>
	void SetVector(const CVector3& vec)
	{
		m_vector = vec;
	}
	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const CVector3& GetPosition() const
	{
		return m_position;
	}
private:
	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();
	/// <summary>
	/// 削除
	/// </summary>
	void Delete();
	SkinModel m_skinModel;								//スキンモデル。
	CharacterController m_charaCon;						//キャラクターコントローラー
	CVector3 m_position = CVector3::Zero();				//位置
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_vector;									//ベクトル
	Player* m_player = nullptr;							//プレイヤー
	int m_waitTimer = 0;								//攻撃待ち時間
	int m_deleteTimer = 0;								//削除タイマー
	bool m_isAttack = false;							//攻撃した。
};

