#pragma once
#include "EnemyBase.h"
class EnemyBall final : public EnemyBase
{
public:
	EnemyBall();
	void Update() override;
	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const CVector3& GetPositon() const
	{
		return m_position;
	}
	/// <summary>
	/// �R���Ă邩�ǂ���
	/// </summary>
	/// <returns>�R��ꂽ��</returns>
	bool GetIsKicked() const
	{
		return m_isKicked;
	}
private:
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
	/// <summary>
	/// �ʏ��
	/// </summary>
	void Ball();
private:
	CSoundSource* m_pokoSE = nullptr;	//���ʉ�
	int m_waitTimer = 0;			//�ҋ@�^�C�}�[
	int m_deleteTimer = 0;			//�폜�^�C�}�[
	bool m_isAttack = false;		//�U���������ǂ���
	bool m_isAttacked = false;		//�U�����ꂽ���ǂ���
	bool m_isChangeModel = false;		//���f���`�F���W�t���O
	bool m_isKicked = false;			//�R��ꂽ���ǂ���
	bool m_isPlayerJump = false;		//�v���C���[����񂾂��ǂ���
	bool m_isBallAttack = false;		//�{�[����ԍU���ł��邩�ǂ���
	bool m_isApproachAgain = false;		//�āX�߂Â������ǂ���
};

