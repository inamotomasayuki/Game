#pragma once
#include "physics/PhysicsStaticObject.h"
#include "Button.h"
class Wall final : public IGameObject
{
public:
	Wall();
	~Wall();
	/*!
	* @brief �X�V
	*/
	void Update() override;
	/*!
	* @brief �`��
	*/
	void Draw() override;
	/// <summary>
	/// ������
	/// </summary>
	void Init();
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
private:
	SkinModel m_skinModel;								//�X�L�����f��
	CVector3 m_position = { 300.0f,0.0f,0.0f };			//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	PhysicsStaticObject m_physicsStaticObject;			//�ÓI�����I�u�W�F�N�g
	bool m_isInit = false;								//�����������H
};

