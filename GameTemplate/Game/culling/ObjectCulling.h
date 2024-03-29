/*!
 *@brief	オブジェクトのカリング処理のインターフェースクラス。
 */
#pragma once
#include "Aabb.h"
 /*!
  *@brief	CPUでの早期カリング処理のインターフェースクラス。
  */
class IObjectCulling {
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	IObjectCulling() {}
	/*!
	 *@brief	デストラクタ。
	 */
	virtual ~IObjectCulling() {}
	/*!
	 *@brief	カリングアルゴリズムを実行。
	 */
	virtual void Execute(const Aabb& aabb) = 0;
	/*!
	 *@brief	カリングされているか判定。
	 */
	bool IsCulling() const
	{
		return m_isCulling;
	}
protected:
	/*!
	 *@brief	カリングフラグを設定。
	 */
	void SetCullingFlag(bool flag)
	{
		m_isCulling = flag;
	}
private:
	bool	m_isCulling = false;
};