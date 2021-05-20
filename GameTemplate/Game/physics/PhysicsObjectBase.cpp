/*!
 * @brief	物理オブジェクトのベースクラス。
 */
#include "stdafx.h"
#include "PhysicsObjectBase.h"
#include "CapsuleCollider.h"
#include "MeshCollider.h"
#include "BoxCollider.h"
using namespace std;

void PhysicsObjectBase::CreateBox(CVector3 pos, CQuaternion rot, CVector3 size)
{
	Release();
	auto boxCollider = make_unique<BoxCollider>();
	boxCollider->Create(size);
	m_collider = move(boxCollider);
	CreateCommon(pos, rot);
}
	
void PhysicsObjectBase::CreateCapsule(CVector3 pos, CQuaternion rot, float radius, float height)
{
	Release();
	auto capusuleCollider = make_unique<CapsuleCollider>();
	capusuleCollider->Create(radius, height);
	m_collider = move(capusuleCollider);
	CreateCommon(pos, rot);
}

void PhysicsObjectBase::CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, const SkinModel& skinModel)
{
	Release();
	CMatrix mScale;
	mScale.MakeScaling(scale);
	auto meshCollider = make_unique<MeshCollider>();
	meshCollider->CreateFromSkinModel(skinModel, &mScale);
	m_collider = move(meshCollider);
	CreateCommon(
		pos,
		rot
	);
}
