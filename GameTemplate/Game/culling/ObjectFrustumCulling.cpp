/*!
 *@brief	フラスタムカリング処理。
 */
#include "stdafx.h"
#include "ObjectFrustumCulling.h"

 /*!
  *@brief	コンストラクタ。
  */
ObjectFrustumCulling::ObjectFrustumCulling()
{
}
/*!
 *@brief	デストラクタ。
 */
ObjectFrustumCulling::~ObjectFrustumCulling()
{
}
/*!
 *@brief	カリングアルゴリズムの実行。
 */
void ObjectFrustumCulling::Execute(const Aabb& aabb)
{
	const CMatrix& viewProjMatrix = g_camera3D.GetViewMatrix() * g_camera3D.GetProjectionMatrix();
	SetCullingFlag(false);
	//CBoxの８頂点をスクリーン空間の正規化座標系に変換する。
	//x、yが1.0〜-1.0、zが0.0〜1.0の範囲内にいたら画面内にいるということになる。
	//8頂点すべてが画面の外ならカリングする。
	auto vMax = CVector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	auto vMin = CVector3(FLT_MAX, FLT_MAX, FLT_MAX);
	for (int i = 0; i < 8; i++) {
		CVector4 vertPos(aabb.GetVertexPosition(i));
		viewProjMatrix.Mul(vertPos);
		vertPos.x /= vertPos.w;
		vertPos.y /= vertPos.w;
		vertPos.z /= vertPos.w;
		vMax.Max({ vertPos.x, vertPos.y, vertPos.z });
		vMin.Min({ vertPos.x, vertPos.y, vertPos.z });
	}
	//オブジェクトの可視判定
	if (vMax.x < -1.0f
		|| vMin.x > 1.0f
		|| vMax.y < -1.0f
		|| vMin.y > 1.0f
		) {
		SetCullingFlag(true);
	}
}