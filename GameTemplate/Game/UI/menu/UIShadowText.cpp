#include "stdafx.h"
#include "UIShadowText.h"
namespace {
	const CVector2 MENU_POS = { 200.0f,120.0f };				//���j���[���W
	const CVector2 OPTIONLIST_POS = { 230.0f,190.0f };			//�I�v�V�������X�g���W
	const float ADD_MENU_POS_Y = 460.0f;						//���Z���j���[���W
	const float ADD_OPTIONLIST_POS_Y = 120.0f;					//���Z�I�v�V�������X�g���W
	const CVector4 COLOR = { 0.3f,0.3f,0.3f,1.0f };				//�F
	const CVector2 SHADOW_POS = { 3.0f,3.0f };					//�e�̍��W
	const float SHADOW_COLOR_POW = 5.0f;						//�e�̐F
	const CVector2 PIVOT = { 27.8f,21.8f };						//�s�{�b�g
}
UIShadowText::UIShadowText()
{	
	//������
	//���W�A�F
	auto addPos = CVector2::Zero();
	//���j���[
	for (int i = 0; i < m_uiData->enMenu_Num; i++) {
		m_menuFontColor[i] = COLOR;
		m_menuFontPosition[i] = MENU_POS + addPos;
		addPos.y += ADD_MENU_POS_Y;
	}
	//���j���[�̉e
	for (int i = 0; i < m_uiData->enMenu_Num; i++) {
		m_shadowMenuFontPosition[i] = m_menuFontPosition[i] + SHADOW_POS;
		m_shadowMenuFontColor[i] = ShadowColor(m_menuFontColor[i]);
	}
	addPos = CVector2::Zero();
	//�I�v�V�������X�g
	for (int i = 0; i < m_uiData->enOptionList_Num; i++) {
		m_optionListTextColor[i] = COLOR;
		m_optionListTextPosition[i] = OPTIONLIST_POS + addPos;
		addPos.y += ADD_OPTIONLIST_POS_Y;
	}
	//�I�v�V�������X�g�̉e
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
	//�ړ�����
	Move();
	//���j���[�̑I�����̐F�̍X�V
	ColorUpdate(
		m_menuFontColor,
		m_uiData->enMenu_Num,
		m_uiData->GetMenuState(),
		CVector4::White(),
		COLOR
	);
	//���j���[�̉e�̐F
	for (int i = 0; i < m_uiData->enMenu_Num; i++) {
		m_shadowMenuFontColor[i] = ShadowColor(m_menuFontColor[i]);
	}
	//�I�v�V�������X�g�̑I�����̐F�̍X�V
	ColorUpdate(
		m_optionListTextColor,
		m_uiData->enOptionList_Num,
		m_uiData->GetOptionListState(),
		CVector4::White(),
		COLOR
	);
	//�I�v�V�������X�g�̉e�̐F
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
		//�I���A�C�R��
		wchar_t text[256];
		swprintf_s(text, L"��");
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
		//���j���[
		m_font.DrawScreenPos(
			m_uiData->GetMenuTextData(i),
			m_shadowMenuFontPosition[i],
			m_shadowMenuFontColor[i]
		);
	}
	for (int i = 0; i < m_uiData->enMenu_Num; i++) {
		//���j���[�̉e
		m_font.DrawScreenPos(
			m_uiData->GetMenuTextData(i),
			m_menuFontPosition[i],
			m_menuFontColor[i]
		);
	}
	if (m_uiData->GetOptionPageState() >= m_uiData->enOptionPage_two) {
		for (int i = 0; i < m_uiData->enOptionList_Num; i++) {
			//�I�v�V�������X�g
			m_font.DrawScreenPos(
				m_uiData->GetOptionListTextData(i),
				m_shadowOptionListTextPosition[i],
				m_shadowOptionListTextColor[i],
				m_optionListScale
			);
		}
		for (int i = 0; i < m_uiData->enOptionList_Num; i++) {
			//�I�v�V�������X�g�̉e
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
	//�I���A�C�R�����W�ݒ�
	if (m_uiData->GetPageState() == m_uiData->enPage_one) {
		SetSelectPos(m_menuFontPosition, m_uiData->GetMenuState(), m_uiData->enMenu_Num, 2.0f, 21.0f);
	}
	if (m_uiData->GetOptionPageState() == m_uiData->enOptionPage_two) {
		SetSelectPos(m_optionListTextPosition, m_uiData->GetOptionListState(), m_uiData->enOptionList_Num, 5.0f, 18.0f);
	}
	//�I���A�C�R����]
	m_selectRotation += 0.08f;
	if (m_selectRotation >= 360) {
		m_selectRotation = 0.0f;
	}
}
void UIShadowText::Move()
{
	//���j���[
	MovePosUpdate(
		m_menuFontPosition,
		m_uiData->enMenu_Num
	);
	//���j���[�̉e
	MovePosUpdate(
		m_shadowMenuFontPosition,
		m_uiData->enMenu_Num
	);
	//�I�v�V�������X�g
	MovePosUpdate(
		m_optionListTextPosition,
		m_uiData->enOptionList_Num
	);
	//�I�v�V�������X�g�̉e
	MovePosUpdate(
		m_shadowOptionListTextPosition,
		m_uiData->enOptionList_Num
	);

}

CVector4 UIShadowText::ShadowColor(const CVector4& baseColor)
{
	//���̐F����Z������
	CVector4 color;
	color.x = baseColor.x / SHADOW_COLOR_POW;
	color.y = baseColor.y / SHADOW_COLOR_POW;
	color.z = baseColor.z / SHADOW_COLOR_POW;
	color.w = 1.0f;
	return color;
}