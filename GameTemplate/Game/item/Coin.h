#pragma once
#include "../player/Player.h"
#include "../enemy/EnemyBall.h"
#include "physics/PhysicsGhostObject.h"
#include "sound/SoundSource.h"
class Game;
class Coin final : public IGameObject
{
public:
	Coin();
	~Coin();
	/*!
	* @brief �X�V
	*/
	void Update() override;
	/*!
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
	/// �X�L�����f���̎擾
	/// </summary>
	/// <returns>�X�L�����f��</returns>
	SkinModel* GetSkinModel()
	{
		return &m_skinModel;
	}
	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const CVector3& GetPositon() const
	{
		return m_position;
	}
	/// <summary>
	/// �R�C�������
	/// </summary>
	void SetCoinGet()
	{
		m_coinGetFlag = true;
	}
private:
	/// <summary>
	/// ��]
	/// </summary>
	void Rotation();
	/// <summary>
	/// �R�C�����l��
	/// </summary>
	void GetCoin();
private:
	SkinModel m_skinModel;				//�X�L�����f���B
	PhysicsGhostObject m_ghostObject;				//�S�[�X�g

	CVector3 m_position = CVector3::Zero();					//���W
	CQuaternion m_rotation = CQuaternion::Identity();		//��]
	CQuaternion m_addRot = CQuaternion::Identity();			//���Z��]
	CVector3 m_scale = CVector3::One();						//�g�嗦�B
	CVector3 m_moveSpeed = CVector3::Zero();				//�ړ����x

	Player* m_player = nullptr;				//�v���C���[
	Game* m_game = nullptr;					//�Q�[��
	EnemyBall* m_enemyBall = nullptr;		//�G��
	int m_timer = 0;						//�^�C�}�[
	bool m_coinGetFlag = false;				//�R�C���擾�t���O
	CSoundSource* m_se = nullptr;			//���ʉ�
	bool m_isInit = false;					//��]������
};

