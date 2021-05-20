#pragma once



class ICollider;

//���̏��B
struct RigidBodyInfo {

	CVector3 pos = CVector3::Zero();			//���W�B
	CQuaternion rot = CQuaternion::Identity();	//��]�B
	CVector3 scale = CVector3::One();			//�g�嗦
	ICollider* collider = nullptr;				//�R���C�_�[�B
	float mass = 0.0f;							//���ʁB

};
//���̃N���X�B
class RigidBody
{
	btRigidBody*			rigidBody = nullptr;		//���́B
	btDefaultMotionState*	myMotionState = nullptr;	//���[�V�����X�e�[�g�B
public:

	~RigidBody();
	void Release();
	void Create(RigidBodyInfo& rbInfo);
	btRigidBody* GetBody()
	{
		return rigidBody;
	}
	/*!
	* @brief	�����I�u�W�F�N�g�̍��W�Ɖ�]��ݒ�
	*@param[in]	pos			���W�B
	*@param[in]	rot			��]�B
	*/
	void SetPositionAndRotation(const CVector3& pos, const CQuaternion& rot)
	{
		btTransform trans;
		btVector3 btPos;
		pos.CopyTo(btPos);
		trans.setOrigin(btPos);
		btQuaternion btRot;
		rot.CopyTo(btRot);
		trans.setRotation(btRot);
		rigidBody->setWorldTransform(trans);
	}

};

