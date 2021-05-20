#include "stdafx.h"
#include "UIShadowText.h"
namespace {
	const CVector2 MENU_POS = { 200.0f,120.0f };				//メニュー座標
	const CVector2 OPTIONLIST_POS = { 230.0f,190.0f };			//オプションリスト座標
	const float ADD_MENU_POS_Y = 460.0f;						//加算メニュー座標
	const float ADD_OPTIONLIST_POS_Y = 120.0f;					//加算オプションリスト座標
	const CVector4 COLOR = { 0.3f,0.3f,0.3f,1.0f };				//色
	const CVector2 SHADOW_POS = { 3.0f,3.0f };					//影の座標
	const float SHADOW_COLOR_POW = 5.0f;						//影の色
	const CVector2 PIVOT = { 27.8f,21.8f };						//ピボット
}
UIShadowText::UIShadowText()
{	
	//初期化
	//座標、色
	auto addPos = CVector2::Zero();
	//メニュー
	for (int i = 0; i < m_uiData->enMenu_Num; i++) {
		m_menuFontColor[i] = COLOR;
		m_menuFontPosition[i] = MENU_POS + addPos;
		addPos.y += ADD_MENU_POS_Y;
	}
	//メニューの影
	for (int i = 0; i < m_uiData->enMenu_Num; i++) {
		m_shadowMenuFontPosition[i] = m_menuFontPosition[i] + SHADOW_POS;
		m_shadowMenuFontColor[i] = ShadowColor(m_menuFontColor[i]);
	}
	addPos = CVector2::Zero();
	//オプションリスト
	for (int i = 0; i < m_uiData->enOptionList_Num; i++) {
		m_optionListTextColor[i] = COLOR;
		m_optionListTextPosition[i] = OPTIONLIST_POS + addPos;
		addPos.y += ADD_OPTIONLIST_POS_Y;
	}
	//オプションリストの影
	for (int i = 0; i < m_uiData->enOptionList_Num; i++) {
		m_shadowOptionListTextPosition[i] = m_optionListTextPosition[i] + SHADOW_POS;
		m_shadowOptionListTextColor[i] = ShadowColor(m_optionListTextColor[i]);
	}

	m_optionListScale *= 0.8f;
}


UIShadowText::~UIShadowText()
{
}

void UIShadowText::Update()
{
	//移動処理
	Move();
	//メニューの選択時の色の更新
	ColorUpdate(
		m_menuFontColor,
		m_uiData->enMenu_Num,
		m_uiData->GetMenuState(),
		CVector4::White(),
		COLOR
	);
	//メニューの影の色
	for (int i = 0; i < m_uiData->enMenu_Num; i++) {
		m_shadowMenuFontColor[i] = ShadowColor(m_menuFontColor[i]);
	}
	//オプションリストの選択時の色の更新
	ColorUpdate(
		m_optionListTextColor,
		m_uiData->enOptionList_Num,
		m_uiData->GetOptionListState(),
		CVector4::White(),
		COLOR
	);
	//オプションリストの影の色
	for (int i = 0; i < m_uiData->enOptionList_Num; i++) {
		m_shadowOptionListTextColor[i] = ShadowColor(m_optionListTextColor[i]);
	}
	SelectControl();
}

void UIShadowText::DrawFont()
{	
	if (m_uiData->GetPageState() == m_uiData->enPage_one 
		&& m_uiData->GetOptionPageState() == m_uiData->enOptionPage_one
		|| m_uiData->GetOptionPageState() == m_uiData->enOptionPage_two) {
		//選択アイコン
		wchar_t text[256];
		swprintf_s(text, L"＊");
		m_font.DrawScreenPos(
			text,
			m_selectPos,
			m_selectColor,
			CVector2::One(),
			PIVOT,
			m_selectRotation
		);
	}
	for (int i = 0; i < m_uiData->enMenu_Num; i++) {
		//メニュー
		m_font.DrawScreenPos(
			m_uiData->GetMenuTextData(i),
			m_shadowMenuFontPosition[i],
			m_shadowMenuFontColor[i]
		);
	}
	for (int i = 0; i < m_uiData->enMenu_Num; i++) {
		//メニューの影
		m_font.DrawScreenPos(
			m_uiData->GetMenuTextData(i),
			m_menuFontPosition[i],
			m_menuFontColor[i]
		);
	}
	if (m_uiData->GetOptionPageState() >= m_uiData->enOptionPage_two) {
		for (int i = 0; i < m_uiData->enOptionList_Num; i++) {
			//オプションリスト
			m_font.DrawScreenPos(
				m_uiData->GetOptionListTextData(i),
				m_shadowOptionListTextPosition[i],
				m_shadowOptionListTextColor[i],
				m_optionListScale
			);
		}
		for (int i = 0; i < m_uiData->enOptionList_Num; i++) {
			//オプションリストの影
			m_font.DrawScreenPos(
				m_uiData->GetOptionListTextData(i),
				m_optionListTextPosition[i],
				m_optionListTextColor[i],
				m_optionListScale
			);
		}
	}
}
void UIShadowText::SelectControl()
{
	//選択アイコン座標設定
	if (m_uiData->GetPageState() == m_uiData->enPage_one) {
		SetSelectPos(m_menuFontPosition, m_uiData->GetMenuState(), m_uiData->enMenu_Num, 2.0f, 21.0f);
	}
	if (m_uiData->GetOptionPageState() == m_uiData->enOptionPage_two) {
		SetSelectPos(m_optionListTextPosition, m_uiData->GetOptionListState(), m_uiData->enOptionList_Num, 5.0f, 18.0f);
	}
	//選択アイコン回転
	m_selectRotation += 0.08f;
	if (m_selectRotation >= 360) {
		m_selectRotation = 0.0f;
	}
}
void UIShadowText::Move()
{
	//メニュー
	MovePosUpdate(
		m_menuFontPosition,
		m_uiData->enMenu_Num
	);
	//メニューの影
	MovePosUpdate(
		m_shadowMenuFontPosition,
		m_uiData->enMenu_Num
	);
	//オプションリスト
	MovePosUpdate(
		m_optionListTextPosition,
		m_uiData->enOptionList_Num
	);
	//オプションリストの影
	MovePosUpdate(
		m_shadowOptionListTextPosition,
		m_uiData->enOptionList_Num
	);

}

CVector4 UIShadowText::ShadowColor(const CVector4& baseColor)
{
	//元の色から濃くする
	CVector4 color;
	color.x = baseColor.x / SHADOW_COLOR_POW;
	color.y = baseColor.y / SHADOW_COLOR_POW;
	color.z = baseColor.z / SHADOW_COLOR_POW;
	color.w = 1.0f;
	return color;
}