#pragma once
#include "physics/PhysicsGhostObject.h"
#include "physics/PhysicsStaticObject.h"
#include "character/CharacterController.h"
class MoveFloor final : public IGameObject
{
public:
	MoveFloor();
	~MoveFloor();
	/*!
	*@brief �X�V
	*/
	void Update() override;
	/*!
	*@brief �`��
	*/
	void Draw() override;
	/*!
	*@brief ������
	*/
	void Init();
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/*!
	*@brief �L�����R���̏�����
	*@param[in]	pos	���W
	*/
	void InitCharaCon(const CVector3& pos)
	{
		//�L�����N�^�[�R���g���[���[
		m_charaCon.Init(
			0.0f,			//���a
			0.0f,			//����
			pos								//�������W
		);
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
	/// �S�[�X�g�̎擾
	/// </summary>
	/// <returns>�S�[�X�g</returns>
	const PhysicsGhostObject* GetGhost() const
	{
		return &m_ghostObject;
	}
	const CVector3& GetPosition() const
	{
		return m_position;
	}

private:
	/// <summary>
	/// ����
	/// </summary>
	void RoundTrip();
	/*!
	*@brief�@EnState
	*�@�����X�e�[�g
	*/
	enum EnState {
		enState_right,		//�s������
		enState_left		//������
	};
	EnState m_state = enState_right;		//�X�e�[�g

	SkinModel m_skinModel;							//�X�L�����f��
	PhysicsStaticObject m_staticObject;				//�ÓI�I�u�W�F�N�g
	PhysicsGhostObject m_ghostObject;				//�S�[�X�g
	CharacterController m_charaCon;					//�L�����R��
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x
	int m_timer = 0;		//�^�C�}�[
	bool m_isInit = false;					//�����������H
};

