#pragma once
#include "physics/PhysicsGhostObject.h"
#include "sound/SoundSource.h"
namespace {
	const float ITEM_END_POS_UP = 80.0f;				//�A�C�e���ŏI�ʒu
	const float ITEM_END_POS_DOWN = 120.0f;				//�A�C�e���ŏI�ʒu
}
class Item final : public IGameObject
{
public:
	Item();
	~Item();
	void Update() override;
	void Draw() override;
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
		m_posUp = m_position.y + ITEM_END_POS_UP;
		m_posDown = m_position.y - ITEM_END_POS_DOWN;
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
	/// �擾������ݒ�
	/// </summary>
	void SetIsGet()
	{
		m_isGet = true;
	}
	/// <summary>
	/// �q�b�v�h���b�v���ꂽ�B
	/// </summary>
	void IsHipDrop()
	{
		m_isHipDrop = true;
	}
private:
	/// <summary>
	/// ��]
	/// </summary>
	void Rotation();
private:
	SkinModel m_skinModel;							//�X�L�����f��
	PhysicsGhostObject m_ghostObject;				//�S�[�X�g
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CSoundSource* m_se = nullptr;						//���ʉ�
	CVector3 m_boxPos;									//���̈ʒu
	float m_posUp = 0.0f;								//�オ��ʒu
	float m_posDown = 0.0f;								//������ʒu	
	bool m_isGet = false;								//�擾���ꂽ��
	bool m_isHipDrop = false;							//�q�b�v�h���b�v���ꂽ��
	bool m_isInit = false;								//�S�[�X�g������
};	

