/*!
 *@brief	フラスタムカリング処理。
 */
#pragma once
#include "ObjectCulling.h"
#include "Aabb.h"
 /*!
	  *@brief	フラスタムカリング処理。
	  *@details
	  * オブジェクトを内包するAABBを構成する8頂点がカメラに映らない場合にカリングされます。
	  */
class ObjectFrustumCulling final : public IObjectCulling {
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	ObjectFrustumCulling();
	/*!
	 *@brief	デストラクタ。
	 */
	~ObjectFrustumCulling();
	/*!
	 *@brief	カリングアルゴリズムの実行。
	 *@param[in]	box	カリングを行いたいオブジェクトをバウンディングボックス。
	 */
	void Execute(const Aabb& aabb) override;
};