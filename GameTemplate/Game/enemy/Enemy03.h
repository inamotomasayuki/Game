#pragma once
#include "EnemyBase.h"
#include "EnemyBall.h"

namespace {
	const float PASS_POS = 200.0f;		//�p�X�̈ʒu�A
}

struct Point {
	CVector3 s_position;		//�|�C���g�̍��W
	int s_number;				//�|�C���g�̔ԍ�
};
class Enemy03 final : public EnemyBase
{
public:
	Enemy03();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update() override;
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
		//�p�X
		m_pointList.push_back({ CVector3(m_position.x,m_position.y,m_position.z),1 });				//1�Ԗڂ̃|�C���g
		m_pointList.push_back({ CVector3(m_position.x + PASS_POS,m_position.y,m_position.z),2 });   //2�Ԗڂ̃|�C���g
		m_pointList.push_back({ CVector3(m_position.x,m_position.y,m_position.z + PASS_POS),3 });   //3�Ԗڂ̃|�C���g
		m_point = &m_pointList[0];                              //��Ԗڂ̃|�C���g������
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
	/// �p�X�ړ�
	/// </summary>
	void PassMove();
private:	
	EnemyBall* m_enemyBall = nullptr;	//�G�i�b���j
	std::vector<Point> m_pointList;		//�|�C���g���X�g
	Point* m_point;						//�|�C���g
	int m_waitTimer = 0;			//�ҋ@�^�C�}�[
	bool m_isAttack = false;		//�U���������ǂ���
	bool m_isAttacked = false;		//�U�����ꂽ���ǂ���
	bool m_isChangeModel = false;		//���f���`�F���W�t���O
	bool m_isKicked = false;			//�R��ꂽ���ǂ���
	bool m_isPlayerJump = false;		//�v���C���[����񂾂��ǂ���
	bool m_isBallAttack = false;		//�{�[����ԍU���ł��邩�ǂ���
	bool m_isApproachAgain = false;		//�āX�߂Â������ǂ���
	bool m_isHipDrop = false;			//�q�b�v�h���b�v���ǂ���
};

