/*!
 * @brief	静的オブジェクト。
 */


#include "stdafx.h"
#include "physics/PhysicsStaticObject.h"


PhysicsStaticObject::PhysicsStaticObject()
{
}
PhysicsStaticObject::~PhysicsStaticObject()
{
	g_physics.RemoveRigidBody(m_rigidBody);
}

void PhysicsStaticObject::CreateMeshObject(SkinModel& skinModel, CVector3 pos, CQuaternion rot, CVector3 scale)
{
	CMatrix mScale;
	mScale.MakeScaling(scale);
	//メッシュコライダーを作成。
	if (m_meshCollider.GetBody() == nullptr) {
		m_meshCollider.CreateFromSkinModel(skinModel, &mScale);
	}
	//剛体を作成、
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //剛体に形状(コライダー)を設定する。
	rbInfo.mass = 0.0f;
	rbInfo.pos = pos;
	rbInfo.rot = rot;
	rbInfo.scale = scale;
	m_rigidBody.Create(rbInfo);
	//剛体を物理ワールドに追加する。
	g_physics.AddRigidBody(m_rigidBody);
}

void PhysicsStaticObject::Delete()
{
	g_physics.RemoveRigidBody(m_rigidBody);
	m_rigidBody.Release();
}