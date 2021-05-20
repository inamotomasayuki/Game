#pragma once
#include "physics/PhysicsGhostObject.h"
#include "physics/PhysicsStaticObject.h"
#include "../player/Player.h"
class JumpFloor final : public IGameObject
{
public:
	JumpFloor();
	~JumpFloor();
	/*
	* @brief �X�V
	*/
	void Update() override;
	/*
	* @brief �`��
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
	/// �S�[�X�g�̎擾
	/// </summary>
	/// <returns>�S�[�X�g</returns>
	const PhysicsGhostObject* GetGhost() const
	{
		return &m_ghostObject;
	}
	/*
	* @brief ���W�̎擾
	* return ���W 
	*/
	const CVector3 GetPosition() const
	{
		return m_position;
	}
private:
	SkinModel m_skinModel;							//�X�L�����f��
	PhysicsStaticObject m_staticObject;				//�ÓI�I�u�W�F�N�g
	PhysicsGhostObject m_ghostObject;				//�S�[�X�g
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
};

