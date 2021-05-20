#pragma once
#include "../graphics/effect/EffectEngine.h"
class Player;
class Warp final : public IGameObject
{
public:
	Warp();
	~Warp();
	/*!
	* @brief �X�V
	*/
	void Update() override;
	/*!
	* @brief �`��
	*/
	void Draw() override;	
	
	enum EnState {
		enState_00,
		enState_01,
		enState_Num
	};

	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos, EnState state)
	{
		m_position[state] = pos;
	}
	/// <summary>
	/// ��]�̐ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion& rot, EnState state)
	{
		m_rotation[state] = rot;
	}
	/// <summary>
	/// �g�嗦�̐ݒ�
	/// </summary>
	/// <param name="scale">�g�嗦</param>
	void SetScale(const CVector3& scale, EnState state)
	{
		m_scale[state] = scale;
	}
	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
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
	/// ��]
	/// </summary>
	void Rotation();
private:
	SkinModel m_skinModel[enState_Num];		//�X�L�����f��
	CVector3 m_position[enState_Num];		//�ʒu
	CQuaternion m_rotation[enState_Num];		//��]
	CVector3 m_scale[enState_Num];			//�X�P�[��
	Player* m_player = nullptr;				//�v���C���[
	EffectEngine* m_effect[enState_Num] = { nullptr };		//�G�t�F�N�g
	int m_stateNum;
	bool m_isWarp = false;
	bool m_isPossible = true;
};