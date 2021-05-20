#pragma once
#include "IUIObject.h"
class UIManager final: public IGameObject
{
public:
	UIManager();
	~UIManager();
	/*
	* @brief 更新
	*/
	void Update() override {};
	/*
	* @brief 描画
	*/
	void Draw() override {};
	/*
	* @brief ポーズ中更新
	*/
	void PauseUpdate() override;
	/*
	* @brief 2D描画
	*/
	void Draw2D() override;
	/*
	* @brief フォント描画
	*/
	void DrawFont() override;
private:
	/// <summary>
	/// UIゲームオブジェクトを追加。
	/// </summary>
	/// <param name="objectName">オブジェクト名</param>
	/// <returns></returns>
	template <class T>
	T* NewUIObject()
	{
		T* newObj = new T;
		m_uiList.push_back(newObj);
		return newObj;
	}
	std::list< IUIObject* > m_uiList;	//UIゲームオブジェクトのリスト
};
