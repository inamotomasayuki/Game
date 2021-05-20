#pragma once
#include "physics/PhysicsStaticObject.h"
#include "physics/PhysicsGhostObject.h"

class BackGround final : public IGameObject
{
public:
	BackGround();
	~BackGround();
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
	/// �ÓI�I�u�W�F�N�g�̎擾
	/// </summary>
	/// <returns>�ÓI�I�u�W�F�N�g</returns>
	const PhysicsStaticObject* GetPhysicsStaticObject() const
	{
		return &m_physicsStaticObject;
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
	/// �X�e�[�W01�I�u�W�F�N�g
	/// </summary>
	enum Stage01Obj {
		enStage01Obj_floor0,			//���O
		enStage01Obj_floor1,			//���P
		enStage01Obj_floor2,			//���Q
		enStage01Obj_floor3,			//���R
		enStage01Obj_floor4,			//���S
		enStage01Obj_ceiling,			//�����蔻��p�V��
		enStage01Obj_bridge,			//��
		enStage01Obj_step,				//�i
		enStage01Obj_fence,				//�t�F���X
		enStage01Obj_stoneFence,		//�΂̃t�F���X
		enStage01Obj_square,			//�l�p
		enStage01Obj_physicsFence,		//�����蔻��p�t�F���X
		enStage01Obj_Num				//��
	};
	/// <summary>
	/// �X�e�[�W02�I�u�W�F�N�g
	/// </summary>
	enum Stage02Obj {
		enStage02Obj_floor0,			//���O
		enStage02Obj_floor1,			//���P
		enStage02Obj_square,			//�l�p
		enStage02Obj_step,				//�i
		enStage02Obj_physicsFence,		//�����蔻��p�t�F���X
		enStage02Obj_Num				//��
	};
	/// <summary>
	/// �X�e�[�W01�X�e�[�g�ݒ�
	/// </summary>
	/// <param name="i">�X�e�[�g�ԍ��i�I�u�W�F�N�g�ԍ��j</param>
	void SetStage01ObjState(int i) {
		m_stage01ObjState = i;
	}
	/// <summary>
	/// �X�e�[�W02�X�e�[�g�ݒ�
	/// </summary>
	/// <param name="i">�X�e�[�g�ԍ��i�I�u�W�F�N�g�ԍ��j</param>
	void SetStage02ObjState(int i) {
		m_stage02ObjState = i;
	}
private:
	/// <summary>
	/// �X�e�[�W01������
	/// </summary>
	void Stage01Init();
	/// <summary>
	/// �X�e�[�W�O�Q������
	/// </summary>
	void Stage02Init();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	SkinModel m_skinModel;								//�X�L�����f��
	PhysicsGhostObject m_ghostObject;					//�S�[�X�g
	PhysicsStaticObject m_physicsStaticObject;			//�ÓI�����I�u�W�F�N�g
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	int m_stage01ObjState;				//�X�e�[�W�P�̃X�e�[�g
	int m_stage02ObjState;				//�X�e�[�W�Q�̃X�e�[�g
	bool m_isInit = false;				//�����������H
	bool m_isPhysics = false;			//physics���H
	bool m_isGhost = false;				//�S�[�X�g���H
	bool m_isDraw = true;				//�`�悷��H
};

