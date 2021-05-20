#pragma once
#include "../graphics/effect/EffectEngine.h"
class Player;
class Warp final : public IGameObject
{
public:
	Warp();
	~Warp();
	/*!
	* @brief 更新
	*/
	void Update() override;
	/*!
	* @brief 描画
	*/
	void Draw() override;	
	
	enum EnState {
		enState_00,
		enState_01,
		enState_Num
	};

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos, EnState state)
	{
		m_position[state] = pos;
	}
	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion& rot, EnState state)
	{
		m_rotation[state] = rot;
	}
	/// <summary>
	/// 拡大率の設定
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(const CVector3& scale, EnState state)
	{
		m_scale[state] = scale;
	}
	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const CVector3& GetPosition() const
	{
		return m_position[m_stateNum];
	}
	bool IsWarp() const
	{
		return m_isWarp;
	}
	void SetIsWarp(bool flag)
	{
		m_isWarp = flag;
	}
private:
	/// <summary>
	/// 回転
	/// </summary>
	void Rotation();
private:
	SkinModel m_skinModel[enState_Num];		//スキンモデル
	CVector3 m_position[enState_Num];		//位置
	CQuaternion m_rotation[enState_Num];		//回転
	CVector3 m_scale[enState_Num];			//スケール
	Player* m_player = nullptr;				//プレイヤー
	EffectEngine* m_effect[enState_Num] = { nullptr };		//エフェクト
	int m_stateNum;
	bool m_isWarp = false;
	bool m_isPossible = true;
};