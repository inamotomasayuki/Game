#pragma once
#include "UIText.h"
class UIShadowText final : public UIText 
{
public:
	UIShadowText();
	~UIShadowText();
	/*!
	* @brief �X�V
	*/
	void Update() override;
	/*!
	* @brief �t�H���g�`��
	*/
	void DrawFont() override;
	/*!
	*@brief		�e�̐F����
	*@param[in]	�e�̌��ƂȂ�F
	*/
	CVector4 ShadowColor(const CVector4& baseColor);
private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/*!
	* @brief �I���A�C�R���ʒu�ݒ�
	*/
	void SelectControl();
	CVector2 m_menuFontPosition[UIData::Menu::enMenu_Num];			//���j���[�̈ʒu
	CVector4 m_menuFontColor[UIData::Menu::enMenu_Num];				//���j���[�F
	CVector2 m_shadowMenuFontPosition[UIData::Menu::enMenu_Num];	//���j���[�̉e�̈ʒu
	CVector4 m_shadowMenuFontColor[UIData::Menu::enMenu_Num];		//���j���[�e�̐F
	
	CVector2 m_optionListTextPosition[UIData::OptionList::enOptionList_Num];			//�I�v�V�������X�g�̈ʒu
	CVector4 m_optionListTextColor[UIData::OptionList::enOptionList_Num];				//�I�v�V�������X�g�̐F
	CVector2 m_shadowOptionListTextPosition[UIData::OptionList::enOptionList_Num];		//�I�v�V�������X�g�̉e�̈ʒu
	CVector4 m_shadowOptionListTextColor[UIData::OptionList::enOptionList_Num];			//�I�v�V�������X�g�̉e�̐F

	CVector2 m_optionListScale = CVector2::One();					//�I�v�V�������X�g�̊g�嗦
};

