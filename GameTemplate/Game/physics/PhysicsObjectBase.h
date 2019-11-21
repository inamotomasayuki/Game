/*!
 *@brief	物理オブジェクトのベースクラス。
 */
#pragma once
#include "stdafx.h"
#include "ICollider.h"

	/*!
	 *@brief	物理オブジェクトのベースクラス。
	 *@detail
	 * template methodパターン
	 */
	class PhysicsObjectBase {
	public:
		/*!
		* @brief	ゴーストオブジェクトを解放。
		*@detail
		* 明示的なタイミングでオブジェクトを削除したい場合に呼び出してください。
		*/
		virtual void Release() = 0;
	private:
		/*!
		* @brief	静的物理オブジェクト作成処理の共通処理。
		*/
		virtual void CreateCommon(CVector3 pos, CQuaternion rot) = 0;
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		PhysicsObjectBase()
		{
		}
		/*!
		 *@brief	デストラクタ。
		 */
		virtual ~PhysicsObjectBase()
		{

		}
		/*!
		* @brief	ボックス形状のゴーストオブジェクトを作成。
		*@param[in]	pos			座標。
		 *@param[in]	rot			回転。
		*@param[in]	size		サイズ。
		*/
		void CreateBox(CVector3 pos, CQuaternion rot, CVector3 size);

		/*!
		 * @brief	カプセル形状のゴーストオブジェクトを作成。
		 *@param[in]	pos			座標。
		 *@param[in]	rot			回転。
		 *@param[in]	radius		カプセルの半径。
		 *@param[in]	height		カプセルの高さ。
		 */
		void CreateCapsule(CVector3 pos, CQuaternion rot, float radius, float height);

		/*!
		* @brief	メッシュ形状のゴーストオブジェクトを作成。
		*@param[in]	pos					座標。
		*@param[in]	rot					回転。
		*@param[in]	skinModelData		スキンモデルデータ。
		*/
		void CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, const SkinModel& skinModel);
	protected:
		std::unique_ptr<ICollider> m_collider;	//!<コライダー。
	};