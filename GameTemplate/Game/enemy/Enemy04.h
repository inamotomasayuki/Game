#pragma once
#include "EnemyBase.h"
class Enemy04 final : public EnemyBase
{
public:
	Enemy04();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update() override;
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
	/// �t�@�C�A�{�[������
	/// </summary>
	void FireBallGenerate();
private:
	CSoundSource* m_fireSE = nullptr;	//���ʉ�
	int m_waitTimer = 0;			//�ҋ@�^�C�}�[
	int m_fireGenerateTimer = 0;	//�t�@�C�A�{�[�������^�C�}�[
	bool m_isFireBallGenerate = false;	//�t�@�C�A�{�[�������������B
	bool m_isAttack = false;		//�U���������ǂ���
	bool m_isAttacked = false;		//�U�����ꂽ���ǂ���
};