#pragma once
class Camera
{
public:
	/*!
	 * @brief	�J�����s��A�v���W�F�N�V�����s��̍X�V�B
	 *@details
	 * ���ݐݒ肳��Ă���A�����_�A���_�A��p�Ȃǂ̏������Ƃ�
	 * �J�����s��ƃv���W�F�N�V�����s����X�V���܂��B
	 * ���̊֐����Ă΂Ȃ��ƁA�J�����͓����Ȃ��̂Œ��ӂ��K�v�ł��B
	 */
	void Update();
	/*!
	 * @brief	�J�����s����擾�B
	 */
	const CMatrix& GetViewMatrix() const
	{
		return m_viewMatrix;
	}
	/*!
	 * @brief	�v���W�F�N�V�����s����擾�B
	 */
	const CMatrix& GetProjectionMatrix() const
	{
		return m_projMatrix;
	}
	/*!
	 * @brief	���_���擾�B
	 */
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/*!
	 * @brief	�����_���擾�B
	 */
	const CVector3& GetTarget() const
	{
		return m_target;
	}
	/*!
	 * @brief	�J�����̏�������擾�B
	 */
	const CVector3& GetUp() const
	{
		return m_up;
	}
	/*!
	 * @brief	���_��ݒ�B
	 */
	void SetPosition( const CVector3& pos )
	{
		m_position = pos;
	}
	/*!
	 * @brief	�����_��ݒ�B
	 */
	void SetTarget( const CVector3& target )
	{
		m_target = target;
	}
	/*!
	 * @brief	�J�����̏������ݒ�B
	 */
	void SetUp( const CVector3& up )
	{
		m_up = up;
	}
	/*!
	 * @brief	�����ʂ�ݒ�B
	 */
	void SetFar( float f )
	{
		m_far = f;
	}
	/*!
	 * @brief	�ߕ��ʂ�ݒ�B
	 */
	void SetNear( float n )
	{
		m_near = n;
	}
	/*!
	 * @brief	��p��ݒ�B
	 */
	void SetViewAngle( float angle )
	{
		m_viewAngle = angle;
	}
private:
	CMatrix	m_viewMatrix = CMatrix::Identity();		//�r���[�s��B
	CMatrix m_projMatrix = CMatrix::Identity();		//�v���W�F�N�V�����s��B
	CVector3 m_target = CVector3::Zero();			//�����_�B
	CVector3 m_position = CVector3::Zero();			//���_�B
	CVector3 m_up = CVector3::Up();					//������B
	float m_viewAngle = CMath::DegToRad(60.0f);		//��p�B
	float m_far = 10000.0f;							//�������ʂ܂ł̋����B
	float m_near = 1.0f;							//�ߕ��ʂ܂ł̋����B
};

extern Camera g_camera3D;		//!<3D�J�����B