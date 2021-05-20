#pragma once
#include "physics/PhysicsGhostObject.h"
#include "physics/PhysicsStaticObject.h"
#include "sound/SoundSource.h"

namespace {
	const CVector3 GHOST_SCALE = { 50.0f,1.0f,50.0f };		//�S�[�X�g�̑傫��
	const float GHOST_UNDER_POS = 50.0f;					//���̃S�[�X�g�ʒu
	const float GHOST_UPPER_POS = 30.0f;					//��̃S�[�X�g�ʒu
}

class Box final : public IGameObject
{
public:
	Box();
	~Box();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;
	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;
	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
		m_ghostPos = pos;
		m_ghostPos.y -= GHOST_UNDER_POS;
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
	/// �S�[�X�g���b�V���̎擾
	/// </summary>
	/// <returns>�S�[�X�g���b�V��</returns>
	const PhysicsGhostObject* GetMeshGhost() const
	{
		return &m_meshGhostObject;
	}
	/// <summary>
	/// �Ԃ������ݒ�
	/// </summary>
	/// <param name="contact">�Ԃ��������ǂ���</param>
	void SetIsContact(bool contact)
	{
		m_isContact = contact;
	}
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
	/// <returns>���W�i�ʒu�j</returns>
	const CVector3 GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// �A�C�e���̎��
	/// </summary>
	enum EnItem {
		enItem_mikan,		//�݂���
		enItem_coin,		//�R�C��
		enItem_Num			//��
	};
	/// <summary>
	/// �A�C�e����ސݒ�
	/// </summary>
	/// <param name="item">�A�C�e���̎��</param>
	void SetItem(const EnItem& item)
	{
		m_itemState = item;
	}
	/// <summary>
	/// �q�b�v�h���b�v���ꂽ���ݒ�
	/// </summary>
	/// <param name="hipDrop">�t���O</param>
	void SetIsHipDrop(bool hipDrop) {
		m_isHipDrop = hipDrop;
	}
private:
	SkinModel m_skinModel;								//�X�L�����f��
	PhysicsStaticObject m_staticObject;					//�ÓI�I�u�W�F�N�g
	PhysicsGhostObject m_ghostObject;					//�S�[�X�g
	PhysicsGhostObject m_meshGhostObject;				//�S�[�X�g
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_ghostPos;								//�S�[�X�g�̈ʒu
	CVector3 m_ghostScale = GHOST_SCALE;				//�S�[�X�g�̑傫��
	CSoundSource* m_se = nullptr;						//���ʉ�
	EnItem m_itemState;									//�A�C�e���ǂ�
	bool m_isContact = false;							//�Ԃ��������ǂ���
	bool m_isInitModel = false;							//���f���`�F���W������
	bool m_isHipDrop = false;							//�q�b�v�h���b�v���ꂽ�B
};

