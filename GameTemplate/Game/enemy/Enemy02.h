#pragma once
#include "EnemyBase.h"
class Enemy02 final : public EnemyBase
{
public:
	Enemy02();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update() override;
private:
	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();
	/// <summary>
	/// �U��
	/// </summary>
	void Attack() override;
	/// <summary>
	///	���S
	/// </summary>
	/// <param name="score">�X�R�A</param>
	void Death(int score) override;
	/// <summary>
	/// ��]
	/// </summary>
	void Rotation() override;
	int m_waitTimer = 0;			//�ҋ@�^�C�}�[
	int m_timer = 0;				//�����p�^�C�}�[�@�P�ʁF�b
	float m_jumpSpeed = 0.0f;		//�W�����v���x
	bool m_isAttack = false;		//�U���������ǂ���
	bool m_isAttacked = false;		//�U�����ꂽ���ǂ���
	bool m_isJump = false;			//�W�����v�t���O
	/*!
	*@brief EnState
	*�@�����X�e�[�g
	*/
	enum EnState {
		enState_right,		//�s������
		enState_left,		//������
		enState_Num			//��
	};
	EnState m_state;		//�X�e�[�g
};