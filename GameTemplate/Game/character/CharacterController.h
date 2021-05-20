/*!
* @brief	�L�����N�^�R���g���[���[�B
*/
#pragma once

#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"


/*!
* @brief	�L�����N�^�R���g���[���[�B
*/
class CharacterController {
public:
	CharacterController() {

	}
	~CharacterController()
	{
		RemoveRigidBoby();
	}

	/*!
		* @brief	�������B
		*@param[in]	radius		�J�v�Z���R���C�_�[�̔��a�B
		*@param[in]	height		�J�v�Z���R���C�_�[�̍����B
		*@param[in]	position	�����ʒu�B
		*/
	void Init(float radius, float height, const CVector3& position);
	void SetColliderRadiusAndHeight(float radius, float height)
	{
		m_radius = radius;
		m_height = height;
		m_collider.Create(radius, height);
	}
	/*!
		* @brief	���s�B
		*@param[in]	deltaTime		�o�ߎ��ԁB�P�ʂ͕b�B
		*@param[in, out]	moveSpeed		�ړ����x�B�����ŏd�͉������v�Z����A���̌��ʂ�moveSpeed�ɔ��f����܂��B
		*@return �ړ���̃L�����N�^�[�̍��W�B
		*/
	const CVector3& Execute(float deltaTime, CVector3& moveSpeed);
	/*!
		* @brief	���W���擾�B
		*/
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/*!
		* @brief	���W��ݒ�B
		*/
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/*!
		* @brief	�W�����v��������
		*/
	bool IsJump() const
	{
		return m_isJump;
	}
	/*!
	* @brief	�n�ʏ�ɂ��邩����B
	*/
	bool IsOnGround() const
	{
		return m_isOnGround;
	}
	/*!
	* @brief	�R���C�_�[���擾�B
	*/
	CapsuleCollider* GetCollider()
	{
		return &m_collider;
	}
	/*!
	* @brief	���̂��擾�B
	*/
	RigidBody* GetRigidBody()
	{
		return &m_rigidBody;
	}
	/*!
	* @brief	���̂𕨗��G���W������폜�B�B
	*/
	void RemoveRigidBoby();
	/// <summary>
	/// ���˃x�N�g���̎擾
	/// </summary>
	/// <returns></returns>
	const CVector3 GetReturnVector() const
	{
		return m_returnVector;
	}
	/// <summary>
	/// �ǂɓ����������ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsWallHit() const
	{
		return m_isWallHit;
	}
private:
	CVector3 			m_position = CVector3::Zero();	//���W�B
	CVector3			m_returnVector = CVector3::Zero();		//�܂�Ԃ��x�N�g��
	bool 				m_isJump = false;				//�W�����v���H
	bool				m_isOnGround = true;			//�n�ʂ̏�ɂ���H
	bool				m_isWallHit = false;
	CapsuleCollider		m_collider;						//�R���C�_�[�B
	float				m_radius = 0.0f;
	float				m_height = 0.0f;		
	RigidBody			m_rigidBody;					//���́B
};
