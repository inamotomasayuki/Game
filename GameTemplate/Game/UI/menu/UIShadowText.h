#pragma once
#include "UIText.h"
class UIShadowText final : public UIText 
{
public:
	UIShadowText();
	~UIShadowText();
	/*!
	* @brief 更新
	*/
	void Update() override;
	/*!
	* @brief フォント描画
	*/
	void DrawFont() override;
	/*!
	*@brief		影の色生成
	*@param[in]	影の元となる色
	*/
	CVector4 ShadowColor(const CVector4& baseColor);
private:
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();
	/*!
	* @brief 選択アイコン位置設定
	*/
	void SelectControl();
	CVector2 m_menuFontPosition[UIData::Menu::enMenu_Num];			//メニューの位置
	CVector4 m_menuFontColor[UIData::Menu::enMenu_Num];				//メニュー色
	CVector2 m_shadowMenuFontPosition[UIData::Menu::enMenu_Num];	//メニューの影の位置
	CVector4 m_shadowMenuFontColor[UIData::Menu::enMenu_Num];		//メニュー影の色
	
	CVector2 m_optionListTextPosition[UIData::OptionList::enOptionList_Num];			//オプションリストの位置
	CVector4 m_optionListTextColor[UIData::OptionList::enOptionList_Num];				//オプションリストの色
	CVector2 m_shadowOptionListTextPosition[UIData::OptionList::enOptionList_Num];		//オプションリストの影の位置
	CVector4 m_shadowOptionListTextColor[UIData::OptionList::enOptionList_Num];			//オプションリストの影の色

	CVector2 m_optionListScale = CVector2::One();					//オプションリストの拡大率
};

