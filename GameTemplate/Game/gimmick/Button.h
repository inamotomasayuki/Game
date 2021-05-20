#pragma once
#include "physics/PhysicsStaticObject.h"
#include "physics/PhysicsGhostObject.h"
#include "sound/SoundSource.h"
#include "../time/GameTime.h"
#include "../graphics/2D/Font.h"
class Game;
namespace {
	const float LIMIT_TIMER = 11.0f;			//��������
	const float GHOST_UP_POS_Y = 50.0f;			//�S�[�X�g�̈ʒu���グ��
}
class Button final: public IGameObject
{
public:
	Button();
	~Button();
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
		//���W
		m_position = pos;
		//�������W
		m_initPos = pos;
		//�S�[�X�g���W
		m_ghostPos = pos;
		m_ghostPos.y += GHOST_UP_POS_Y;
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
	/// <summary>
	/// ���Ԃ̎擾
	/// </summary>
	/// <returns></returns>
	float GetTimer() const
	{
		return m_timer;
	}
	/// <summary>
	/// �������ݒ�
	/// </summary>
	void IsPush()
	{
		m_isPush = true;
	}
	/*!
	* @brief ���������t���O��Ԃ�
	* @return �t���O
	*/
	bool GetIsPush()
	{
		return m_isPush;
	}
	/*!
	* @enum EnState
	* �{�^���̎��
	*/
	enum EnState
	{
		enState_0,		//�{�^���O
		enState_1,		//�{�^���P
		enState_2,		//�{�^���Q
		enState_stop,	//�~�߂�
		enState_Num		//��
	};
	/*!
	* @brief�@�{�^����ނ̐ݒ�
	* @param state �{�^���̎��
	*/
	void SetState(const EnState& state)
	{
		m_state = state;
	}
	/*!
	* @brief �{�^���̎�ނ̏�Ԃ�Ԃ�
	* @return �{�^���̎�ނ̏��
	*/
	const EnState& GetState() const
	{
		return m_state;
	}
private:
	SkinModel m_skinModel;								//�X�L�����f��
	CVector3 m_position = CVector3::Zero();				//���W
	CVector3 m_movePos = m_position;				//�ړ��ʒu
	CVector3 m_ghostPos = CVector3::Zero();				//�������W

	CVector3 m_initPos = CVector3::Zero();				//�������W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CSoundSource* m_fumuSE = nullptr;					//���ʉ�
	PhysicsGhostObject m_ghostObject;					//�S�[�X�g
	PhysicsStaticObject m_physicsStaticObject;			//�ÓI�����I�u�W�F�N�g
	Font m_font;										//�t�H���g
	Game* m_game = nullptr;								//�Q�[��
	EnState m_state;									//�{�^���X�e�[�g
	
	float m_timer = LIMIT_TIMER;								//�^�C�}�[
	bool m_isSE = false;								//���ʉ��Ȃ����H
	bool m_isDown = false;								//���������H
	bool m_isPush = false;								//�������H
	bool m_isDelete = false;							//�폜�����H
	bool m_isInit = false;								//�����������H
};

