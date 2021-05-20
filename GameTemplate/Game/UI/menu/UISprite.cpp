#include "stdafx.h"
#include "UISprite.h"
#include "../../option/OptionData.h"

namespace {
	const float VIEW_BOLUME_WIDTH = 1280.0f;		//�r���[�{�����[���̕�
	const float VIEW_BOLUME_HIGHT = 720.0f;			//�r���[�{�����[���̍���
	const float F_NEAR = 0.1f;						//�ߕ���
	const float F_FAR = 100.0f;						//������

	const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//�J�����̈ʒu
	const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//�J�����̒����_
	const CVector3 CAMERA_UP = { 0,1,0 };				//�J�����̏����

	const float MOVE_SPEED = 10.0f;					//�ړ����x

	const float BACK_SPRITE_WIDTH = 900.0f;			//�w��X�v���C�g�̕�
	const float BACK_SPRITE_HIGHT = 600.0f;			//�w��X�v���C�g�̍���
	const float SPRITE_WIDTH = 100.0f;				//�X�v���C�g�̕�
	const float SPRITE_HIGHT = 100.0f;				//�X�v���C�g�̍���

	const CVector2 BAR_PIVOT = { -1.0,0.0f };		//�o�[�̃s�{�b�g
	const float BAR_SPRITE_MULTIPLY_WIDTH = 2.0f;	//�o�[�̃X�v���C�g�̕��ɂ����鐔�l
	const float BAR_SPRITE_HIGHT = 5.0f;			//�o�[�̃X�v���C�g�̍���

	const CVector3 OBJ_POS = { -50.0f,120.0f,0.0f };		//�I�u�W�F�N�g���W
	const CVector3 GIMMICK_POS = { -50.0f,120.0f,0.0f };	//�M�~�b�N���W
	const CVector3 ENEMY_POS = { -50.0f,120.0f,0.0f };		//�G���W
	//���炵�ĕ��ׂ邽�߂ɉ��Z
	const CVector3 ADD_POS = { 105.0f,0.0f,0.0f };		//���Z���W
	//���C�g�����o�[�ʒu
	const CVector3 LIGHT_BAR_POS[UISprite::enLightBar_Num] = {
		{145.0f,145.0f,0.0f},
		{145.0f,105.0f,0.0f},
		{145.0f,65.0f,0.0f},
		{120.0f,-7.0f,0.0f},
		{120.0f,-86.0f,0.0f}
	};
	//�u���[�������o�[�ʒu
	const CVector3 BLOOM_BAR_POS[UISprite::enBloomBar_Num] = {
		{20.0f,153.0f,0.0f},
		{20.0f,23.0f,0.0f}
	};
}
UISprite::UISprite()
{
	m_uiData = &GetUIData();
	//�������������
	Init();
}


UISprite::~UISprite()
{
}

void UISprite::Update()
{
	m_uiData = &GetUIData();
	const auto& m_optionData = &GetOptionData();
	//�ړ�����
	Move();
	//���m�N��������
	MonochromeControl();

	//�т��
	m_lightBarSprite[enLightBar_r].InitCommon(m_optionData->GetCountColorR() * BAR_SPRITE_MULTIPLY_WIDTH, BAR_SPRITE_HIGHT);
	m_lightBarSprite[enLightBar_g].InitCommon(m_optionData->GetCountColorG() * BAR_SPRITE_MULTIPLY_WIDTH, BAR_SPRITE_HIGHT);
	m_lightBarSprite[enLightBar_b].InitCommon(m_optionData->GetCountColorB() * BAR_SPRITE_MULTIPLY_WIDTH, BAR_SPRITE_HIGHT);
	m_lightBarSprite[enLightBar_brightness].InitCommon(m_optionData->GetBrightnessCount() * BAR_SPRITE_MULTIPLY_WIDTH, BAR_SPRITE_HIGHT);
	m_lightBarSprite[enLightBar_skyBrightness].InitCommon(m_optionData->GetSkyBrightnessCount() * BAR_SPRITE_MULTIPLY_WIDTH, BAR_SPRITE_HIGHT);

	m_bloomBarSprite[enBloomBar_lum].InitCommon(m_optionData->GetLumCount() * BAR_SPRITE_MULTIPLY_WIDTH, BAR_SPRITE_HIGHT);
	m_bloomBarSprite[enBloomBar_pow].InitCommon(m_optionData->GetPowCount() * BAR_SPRITE_MULTIPLY_WIDTH, BAR_SPRITE_HIGHT);

	//////�X�V//////
	//�w�i
	m_backSprite.UpdateWorldMatrix(m_backSpritePosition, m_rotation, m_backSpriteScale);
	//�I�u�W�F�N�g
	for (int i = 0; i < m_uiData->enObj_Num; i++) {
		m_objSprite[i].UpdateWorldMatrix(m_objSpritePosition[i], m_rotation, m_objSpriteScale);
	}
	//�M�~�b�N
	for (int i = 0; i < m_uiData->enGimmick_Num; i++) {
		m_gimmickSprite[i].UpdateWorldMatrix(m_gimmickSpritePosition[i], m_rotation, m_gimmickSpriteScale);
	}
	//�G
	for (int i = 0; i < m_uiData->enEnemy_Num; i++) {
		m_enemySprite[i].UpdateWorldMatrix(m_enemySpritePosition[i], m_rotation, m_enemySpriteScale);
	}
	//���C�g�����o�[
	for (int i = 0; i < enLightBar_Num; i++) {
		m_lightBarSprite[i].UpdateWorldMatrix(m_lightBarPos[i], m_rotation, m_barScale, BAR_PIVOT);
	}
	//�u���[�������o�[
	for (int i = 0; i < enBloomBar_Num; i++) {
		m_bloomBarSprite[i].UpdateWorldMatrix(m_bloomBarPos[i], m_rotation, m_barScale, BAR_PIVOT);
	}

}

void UISprite::Draw2D()
{
	CMatrix mView;
	CMatrix mProj;
	mView.MakeLookAt(
		CAMERA_POSITION,
		CAMERA_TARGET,
		CAMERA_UP
	);
	mProj.MakeOrthoProjectionMatrix(VIEW_BOLUME_WIDTH, VIEW_BOLUME_HIGHT, F_NEAR, F_FAR);
	//�w�i
	m_backSprite.Draw(mView, mProj);
	if (m_uiData->GetPageState() == m_uiData->enPage_three) {
		if (m_uiData->GetObjMenuState() == m_uiData->enObjMenu_obj) {
			//�I�u�W�F�N�g
			for (int i = 0; i < m_uiData->enObj_Num; i++) {
				m_objSprite[i].Draw(mView, mProj);
			}
		}
		else if (m_uiData->GetObjMenuState() == m_uiData->enObjMenu_gimmick) {
			//�M�~�b�N
			for (int i = 0; i < m_uiData->enGimmick_Num; i++) {
				m_gimmickSprite[i].Draw(mView, mProj);
			}
		}
		else if (m_uiData->GetObjMenuState() == m_uiData->enObjMenu_enemy) {
			//�G
			for (int i = 0; i < m_uiData->enEnemy_Num; i++) {
				m_enemySprite[i].Draw(mView, mProj);
			}
		}
	}
	if (m_uiData->GetOptionPageState() >= m_uiData->enOptionPage_three) {
		if (m_uiData->GetOptionListState() == m_uiData->enOptionList_light) {
			for (int i = 0; i < enLightBar_Num; i++) {
				m_lightBarSprite[i].Draw(mView, mProj);
			}
		}
		if (m_uiData->GetOptionListState() == m_uiData->enOptionList_bloom) {
			for (int i = 0; i < enBloomBar_Num; i++) {
				m_bloomBarSprite[i].Draw(mView, mProj);
			}
		}
	}
}
void UISprite::Init()
{
	//�������������
	//�t�@�C���p�X�ݒ肵����A���W�ݒ肵����A���m�N���ɂ��Ƃ�����

	//�w�i
	m_backSprite.Init(L"Assets/sprite/uiBack.dds", BACK_SPRITE_WIDTH, BACK_SPRITE_HIGHT);
	//���C�g�����o�[
	for (int i = 0; i < enLightBar_Num; i++) {
		m_lightBarSprite[i].Init(L"Assets/sprite/bar.dds", 0.0f, 0.0f);
		m_lightBarPos[i] = LIGHT_BAR_POS[i];
	}
	//�u���[�������o�[
	for (int i = 0; i < enBloomBar_Num; i++) {
		m_bloomBarSprite[i].Init(L"Assets/sprite/bar.dds", 0.0f, 0.0f);
		m_bloomBarPos[i] = BLOOM_BAR_POS[i];
	}

	auto addPos = CVector3::Zero();
	//�I�u�W�F�N�g
	for (int i = 0; i < m_uiData->enObj_Num; i++) {
		m_objSprite[i].Init(m_uiData->GetObjSpriteFilePath(i), SPRITE_WIDTH, SPRITE_HIGHT);
		m_objSprite[i].SetIsMonochrome(true);
		m_objSpritePosition[i] = OBJ_POS + addPos;
		addPos += ADD_POS;
	}
	addPos = CVector3::Zero();
	//�M�~�b�N
	for (int i = 0; i < m_uiData->enGimmick_Num; i++) {
		m_gimmickSprite[i].Init(m_uiData->GetGimmickSpriteFilePath(i), SPRITE_WIDTH, SPRITE_HIGHT);
		m_gimmickSprite[i].SetIsMonochrome(true);
		m_gimmickSpritePosition[i] = GIMMICK_POS + addPos;
		addPos += ADD_POS;
	}
	addPos = CVector3::Zero();
	//�G
	for (int i = 0; i < m_uiData->enEnemy_Num; i++) {
		m_enemySprite[i].Init(m_uiData->GetEnemySpriteFilePath(i), SPRITE_WIDTH, SPRITE_HIGHT);
		m_enemySprite[i].SetIsMonochrome(true);
		m_enemySpritePosition[i] = ENEMY_POS + addPos;
		addPos += ADD_POS;
	}
}
void UISprite::Move()
{
	//���W�̈ړ�
	m_moveSpeed.x = g_pad->GetRStickXF() * MOVE_SPEED;
	m_moveSpeed.y = g_pad->GetRStickYF() * MOVE_SPEED;

	//�w�i
	m_backSpritePosition.x += m_moveSpeed.x;
	m_backSpritePosition.y += m_moveSpeed.y;
	//�I�u�W�F�N�g
	for (int i = 0; i < m_uiData->enObj_Num; i++) {
		m_objSpritePosition[i].x += m_moveSpeed.x;
		m_objSpritePosition[i].y += m_moveSpeed.y;
	}
	//�M�~�b�N
	for (int i = 0; i < m_uiData->enGimmick_Num; i++) {
		m_gimmickSpritePosition[i].x += m_moveSpeed.x;
		m_gimmickSpritePosition[i].y += m_moveSpeed.y;
	}
	//�G
	for (int i = 0; i < m_uiData->enEnemy_Num; i++) {
		m_enemySpritePosition[i].x += m_moveSpeed.x;
		m_enemySpritePosition[i].y += m_moveSpeed.y;
	}
	//���C�g�����o�[
	for (int i = 0; i < enLightBar_Num; i++) {
		m_lightBarPos[i].x += m_moveSpeed.x;
		m_lightBarPos[i].y += m_moveSpeed.y;
	}
	//�u���[�������o�[
	for (int i = 0; i < enBloomBar_Num; i++) {
		m_bloomBarPos[i].x += m_moveSpeed.x;
		m_bloomBarPos[i].y += m_moveSpeed.y;
	}
}
void UISprite::MonochromeControl()
{
	if (m_uiData->GetPageState() == m_uiData->enPage_three) {
		if (m_uiData->GetObjMenuState() == m_uiData->enObjMenu_enemy) {
			//�G
			MonochromeUpdate(
				m_uiData->GetEnemyState(),
				m_uiData->enEnemy_Num,
				m_enemySprite
			);
		}
		else if (m_uiData->GetObjMenuState() == m_uiData->enObjMenu_gimmick) {
			//�M�~�b�N
			MonochromeUpdate(
				m_uiData->GetGimmickState(),
				m_uiData->enGimmick_Num,
				m_gimmickSprite
			);
		}
		else if (m_uiData->GetObjMenuState() == m_uiData->enObjMenu_obj) {
			//�I�u�W�F�N�g
			MonochromeUpdate(
				m_uiData->GetObjState(),
				m_uiData->enObj_Num,
				m_objSprite
			);
		}
	}
	else {
		//�S�����m�N���ɂ��Ƃ�
		for (int i = 0; i < m_uiData->enObj_Num; i++) {
			m_objSprite[i].SetIsMonochrome(true);
		}
		for (int i = 0; i < m_uiData->enGimmick_Num; i++) {
			m_gimmickSprite[i].SetIsMonochrome(true);
		}
		for (int i = 0; i < m_uiData->enEnemy_Num; i++) {
			m_enemySprite[i].SetIsMonochrome(true);
		}
	}
}
void UISprite::MonochromeUpdate(int state, int en_Num, Sprite* sprite)
{
	for (int i = 0; i < en_Num; i++) {
		if (state == i) {
			sprite[i].SetIsMonochrome(false);
		}
		else {
			sprite[i].SetIsMonochrome(true);
		}
	}
}