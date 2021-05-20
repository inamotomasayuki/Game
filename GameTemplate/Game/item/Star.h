#pragma once
#include "physics/PhysicsGhostObject.h"
class Player;
class Game;
class Star final : public IGameObject
{
public:
	Star();
	~Star();
	/*
	* @brief �X�V
	*/
	void Update() override;
	/*
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
	/// �S�[�X�g�̎擾
	/// </summary>
	/// <returns></returns>
	const PhysicsGhostObject* GetGhost() const
	{
		return &m_ghost;
	}
	/// <summary>
	/// ���擾�t���O�̎擾
	/// </summary>
	/// <returns>���擾�t���O</returns>
	bool GetStarFlag() const
	{
		return m_getStar;
	}
private:
	/// <summary>
	/// ��]
	/// </summary>
	void Rotation();
private:
	SkinModel m_skinModel;									//�X�L�����f��
	PhysicsGhostObject m_ghost;								//�S�[�X�g
	CVector3 m_position = CVector3::Zero();					//���W
	CQuaternion m_rotation = CQuaternion::Identity();		//��]
	CVector3 m_scale = CVector3::One();						//�g�嗦�B
	int m_timer = 0;						//���擾�t���O���Ă�܂ł̃^�C�}�[�@�P�ʁF�b
	bool m_getStar = false;					//���擾�t���O
	Player* m_player = nullptr;				//�v���C���[
	Game* m_game = nullptr;					//�Q�[��
};

