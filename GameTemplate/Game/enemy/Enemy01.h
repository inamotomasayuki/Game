#pragma once
#include "EnemyBase.h"
class Enemy01 final : public EnemyBase
{
public:
	Enemy01();
	void Update() override;
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
		//�����ʒu
		m_initialPos = pos;
	}
private:
	/// <summary>
	/// �ǐ�
	/// </summary>
	void Search();
	/// <summary>
	/// �����ʒu�ɖ߂�
	/// </summary>
	void Return();
	/// <summary>
	/// ��]
	/// </summary>
	void Rotation() override;
	/// <summary>
	/// �U��
	/// </summary>
	void Attack() override;
	/// <summary>
	///	���S
	/// </summary>
	/// <param name="score">�X�R�A</param>
	void Death(int score) override;

private:
	CVector3 m_initialPos = CVector3::Zero();	//�����ʒu	
	int m_waitTimer = 0;						//�ҋ@�^�C�}�[
	bool m_isAttack = false;					//�U���������ǂ���
	bool m_isAttacked = false;					//�U�����ꂽ���ǂ���
};