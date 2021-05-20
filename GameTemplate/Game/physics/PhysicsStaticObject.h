/*!
 * @brief	静的オブジェクト。
 */

#pragma once

#include "physics/MeshCollider.h"
#include "physics/RigidBody.h"


/*!
* @brief	静的物理オブジェクト
*/
class PhysicsStaticObject{
public:
	/*!
		* @brief	コンストラクタ。
		*/
	PhysicsStaticObject();
	/*!
		* @brief	デストラクタ。
		*/
	~PhysicsStaticObject();
	/*!
		* @brief	メッシュの静的オブジェクトを作成。
		*@param[in]	skinModel	スキンモデル。
		*@param[in]	pos			座標。
		*@param[in]	rot			回転。
		*@param[in]	scale       拡大率。
		*/
	void CreateMeshObject(SkinModel& skinModel, CVector3 pos, CQuaternion rot, CVector3 scale);
	/*!
	* @brief	座標と回転を設定。
	*/
	void SetPositionAndRotation(const CVector3& pos, const CQuaternion& rot)
	{
		m_rigidBody.SetPositionAndRotation(pos, rot);
	}
	/// <summary>
	/// 削除
	/// </summary>
	void Delete();
private:
	MeshCollider m_meshCollider;		//!<メッシュコライダー。
	RigidBody m_rigidBody;				//!<剛体。
};
