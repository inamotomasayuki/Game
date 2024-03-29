/*!
 *@brief	AABB
 */
#pragma once
 /*!
  *@brief	Aabb
  */
class Aabb final {
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	Aabb();
	/*!
	 *@brief	初期化。
	 */
	void Init(const CVector3& halfSize);
	/*!
	 *@brief	更新。
	 *@param[in]	worldMatrix。
	 */
	void Update(const CMatrix& worldMatrix);
	/*!
	*@brief	バウンディングボックスを構成する8頂点の座標を取得。
	*@param[in]	vertNo	頂点番号。0〜7の番号を渡してください。
	*/
	const CVector3& GetVertexPosition(unsigned int vertNo) const
	{
		return m_vertexPosition[vertNo];
	}

private:
	CVector3	m_halfSize = CVector3::Zero();		//!<ハーフサイズ。
	CVector3	m_vertexPosition[8];				//!<バウンディングボックスを構成する8頂点の座標。
};