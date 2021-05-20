#pragma once
#include "character/CharacterController.h"

class Player;

class FireBall final : public IGameObject
{
public:
	FireBall();
	~FireBall();
	/*!
	*@brief �X�V
	*/
	void Update() override;
	/*!
	*@brief �`��
	*/
	void Draw() override;
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]�̐ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// �g�嗦�̐ݒ�
	/// </summary>
	/// <param name="scale">�g�嗦</param>
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const CVector3& GetPosition() const
	{
		return m_position;
	}
private:
	SkinModel m_skinModel;								//�X�L�����f��
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_targetPos;								//�v���C���[�ʒu
	CVector3 m_toPos;									//�t�@�C�A�{�[���̈ʒu
	CVector3 m_moveSpeed;								//�ړ����x
	CVector3 m_vectorXZ;								//XZ�x�N�g��
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[
	Player* m_player = nullptr;							//�v���C���[
	int m_deleteTimer = 0;		//�폜�^�C�}�[�@�P�ʁF�b
	float m_jumpSpeed = 0.0f;	//�W�����v���x
	bool m_isJump = false;		//�W�����v�t���O
};

