#include "stdafx.h"
#include "UIData.h"

UIData::UIData()
{
	//�e�L�X�g������
	TextDataInit();
	//�X�v���C�g�̃t�@�C���p�X������
	SpriteFilePathInit();
}

void UIData::TextDataInit()
{
	//���j���[�e�L�X�g�f�[�^
	swprintf_s(m_menutextData[enMenu_list], L"�E���X�g");
	swprintf_s(m_menutextData[enMenu_option], L"���I�v�V������");
	//�I�u�W�F�N�g���j���[�e�L�X�g�f�[�^
	swprintf_s(m_objMenutextData[enObjMenu_gimmick], L"�E�M�~�b�N");
	swprintf_s(m_objMenutextData[enObjMenu_obj], L"�E�I�u�W�F�N�g");
	swprintf_s(m_objMenutextData[enObjMenu_enemy], L"�E�G�L����");
	//�I�u�W�F�N�g�e�L�X�g�f�[�^
	swprintf_s(m_objTextData[enObj_coin], L"�R�C��");
	swprintf_s(m_objTextData[enObj_mikan], L"�݂���");
	swprintf_s(m_objTextData[enObj_star], L"�X�^�[");
	//�M�~�b�N�e�L�X�g�f�[�^
	swprintf_s(m_gimmickTextData[enGiimick_MoveFloor], L"������");
	swprintf_s(m_gimmickTextData[enGimmick_button], L"�{�^��");
	swprintf_s(m_gimmickTextData[enGimmick_box], L"�{�b�N�X");
	swprintf_s(m_gimmickTextData[enGimmick_jumpFloor], L"�W�����v��");
	swprintf_s(m_gimmickTextData[enGimmick_warp], L"���[�v��");
	//�G�e�L�X�g�f�[�^
	swprintf_s(m_enemyTextData[enEnemy_kame], L"�J��");
	swprintf_s(m_enemyTextData[enEnemy_kuribo], L"����ڂ�");
	swprintf_s(m_enemyTextData[enEmemy_wingKuribo], L"�H��\n����ڂ�");
	//���C�g�e�L�X�g�f�[�^
	swprintf_s(m_optionListTextData[enOptionList_light], L"�E���C�g");
	swprintf_s(m_optionListTextData[enOptionList_bloom], L"�E�u���[��");
	//�u���[���e�L�X�g�f�[�^
	swprintf_s(m_bloomTextData[enBloom_luminance], L"�P�x");
	swprintf_s(m_bloomTextData[enBloom_pow], L"����");
	swprintf_s(m_bloomTextData[enBloom_init], L"������");
	//���C�g�e�L�X�g�f�[�^
	swprintf_s(m_lightTextData[enLight_color], L"�F�ݒ�");
	swprintf_s(m_lightTextData[enLight_brightness], L"���邳");
	swprintf_s(m_lightTextData[enLight_skyBrightness], L"��̖��邳");
	swprintf_s(m_lightTextData[enLight_init], L"������");
	//���C�g�J���[�e�L�X�g�f�[�^
	swprintf_s(m_lightColorTextData[enLightColor_r], L"R");
	swprintf_s(m_lightColorTextData[enLightColor_g], L"G");
	swprintf_s(m_lightColorTextData[enLightColor_b], L"B");
}

void UIData::SpriteFilePathInit()
{
	//�I�u�W�F�N�g�X�v���C�g�t�@�C���p�X
	swprintf_s(m_objSpriteFilePath[enObj_coin], L"Assets/sprite/uiCoin.dds");
	swprintf_s(m_objSpriteFilePath[enObj_mikan], L"Assets/sprite/mikan.dds");
	swprintf_s(m_objSpriteFilePath[enObj_star], L"Assets/sprite/star.dds");
	//�M�~�b�N�X�v���C�g�t�@�C���p�X
	swprintf_s(m_gimmickSpriteFilePath[enGiimick_MoveFloor], L"Assets/sprite/moveFloor.dds");
	swprintf_s(m_gimmickSpriteFilePath[enGimmick_button], L"Assets/sprite/button.dds");
	swprintf_s(m_gimmickSpriteFilePath[enGimmick_box], L"Assets/sprite/box.dds");
	swprintf_s(m_gimmickSpriteFilePath[enGimmick_jumpFloor], L"Assets/sprite/jumpFloor.dds");
	swprintf_s(m_gimmickSpriteFilePath[enGimmick_warp], L"Assets/sprite/warp.dds");
	//�G�X�v���C�g�t�@�C���p�X
	swprintf_s(m_enemySpriteFilePath[enEnemy_kame], L"Assets/sprite/kame.dds");
	swprintf_s(m_enemySpriteFilePath[enEnemy_kuribo], L"Assets/sprite/kuribo.dds");
	swprintf_s(m_enemySpriteFilePath[enEmemy_wingKuribo], L"Assets/sprite/wingKuribo.dds");
}
void UIData::Reset()
{
	//�X�e�[�g�����Z�b�g
	m_pageState = static_cast<Page>(0);
	m_optionPageState = static_cast<OptionPage>(0);
	m_menuState = static_cast<Menu>(0);
	m_objMenuState = static_cast<ObjMenu>(0);
	m_objState = static_cast<Obj>(0);
	m_gimmickState = static_cast<Gimmick>(0);
	m_enemyState = static_cast<Enemy>(0);
	m_optionListState = static_cast<OptionList>(0);
	m_bloomState = static_cast<Bloom>(0);
	m_lightState = static_cast<Light>(0);
	m_lightColorState = static_cast<LightColor>(0);
}