#pragma once



class ICollider;

//剛体情報。
struct RigidBodyInfo {

	CVector3 pos = CVector3::Zero();			//座標。
	CQuaternion rot = CQuaternion::Identity();	//回転。
	CVector3 scale = CVector3::One();			//拡大率
	ICollider* collider = nullptr;				//コライダー。
	float mass = 0.0f;							//質量。

};
//剛体クラス。
class RigidBody
{
	btRigidBody*			rigidBody = nullptr;		//剛体。
	btDefaultMotionState*	myMotionState = nullptr;	//モーションステート。
public:

	~RigidBody();
	void Release();
	void Create(RigidBodyInfo& rbInfo);
	btRigidBody* GetBody()
	{
		return rigidBody;
	}
	/*!
	* @brief	物理オブジェクトの座標と回転を設定
	*@param[in]	pos			座標。
	*@param[in]	rot			回転。
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

