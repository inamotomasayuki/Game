#pragma once
#include "../player/Player.h"
class EnemyFireBall final : public IGameObject
{
public:
	EnemyFireBall();
	~EnemyFireBall();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// �x�N�g���̐ݒ�
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	void SetVector(const CVector3& vec)
	{
		m_vector = vec;
	}
	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const CVector3& GetPosition() const
	{
		return m_position;
	}
private:
	/// <summary>
	/// �U��
	/// </summary>
	void Attack();
	/// <summary>
	/// �폜
	/// </summary>
	void Delete();
	SkinModel m_skinModel;								//�X�L�����f���B
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[
	CVector3 m_position = CVector3::Zero();				//�ʒu
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_vector;									//�x�N�g��
	Player* m_player = nullptr;							//�v���C���[
	int m_waitTimer = 0;								//�U���҂�����
	int m_deleteTimer = 0;								//�폜�^�C�}�[
	bool m_isAttack = false;							//�U�������B
};

