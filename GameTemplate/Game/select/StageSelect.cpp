#include "stdafx.h"
#include "StageSelect.h"
#include "../title/Title.h"
#include "Game.h"
#include "GameData.h"
namespace {
	const float VIEW_BOLUME_WIDTH = 1280.0f;		//�r���[�{�����[���̕�
	const float VIEW_BOLUME_HIGHT = 720.0f;			//�r���[�{�����[���̍���
	const float F_NEAR = 0.1f;						//�ߕ���
	const float F_FAR = 100.0f;						//������

	const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//�J�����̈ʒu
	const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//�J�����̒����_
	const CVector3 CAMERA_UP = { 0,1,0 };				//�J�����̏����

	const int STAGE_NUM = 1;				//�X�e�[�W�̐�
	const int SELECT_NUM = 1;				//�Z���N�g�̐�

	const float TOUMEI_ALPHA = 0.3f;			//�A���t�@�l���}�C�i�X
	const float ALPHA_PLUS = 1.0f;			//�A���t�@�l���v���X

	const float BACK_WIDTH = 1280.0f;				//�w�i�̕�
	const float BACK_HIGHT = 720.0f;				//�w�i�̍���
	const float SELECT_WIDTH = 1280.0f;				//�Z���N�g��
	const float SELECT_HIGHT = 720.0f;				//�Z���N�g����
	const float OK_WIDTH = 720.0f;					//OK�̕�
	const float OK_HIGHT = 360.0f;					//OK�̍���
	const float STAGE_ZERO_WIDTH = 100.0f;			//�O�̕�
	const float STAGE_ZERO_HIGHT = 100.0f;			//�O�̍���
	const float STAGE_ONE_WIDTH = 100.0f;			//�P�̕�
	const float STAGE_ONE_HIGHT = 100.0f;			//�P�̍���
	const float LEFT_TRIANGLE_WIDTH = 100.0f;		//���O�p�̕�
	const float LEFT_TRIANGLE_HIGHT = 100.0f;		//���O�p�̍���
	const float RIGHT_TRIANGLE_WIDTH = 100.0f;		//�E�O�p�̕�
	const float RIGHT_TRIANGLE_HIGHT = 100.0f;		//�E�O�p�̍���
	const float UP_TRIANGLE_WIDTH = 100.0f;			//��O�p�̕�
	const float UP_TRIANGLE_HIGHT = 100.0f;			//��O�p�̍���
	const float DOWN_TRIANGLE_WIDTH = 100.0f;		//���O�p�̕�
	const float DOWN_TRIANGLE_HIGHT = 100.0f;		//���O�p�̍���
	const float DELETE_THIS_ALPHA = 1.0f;			//�t�F�[�h�����̃A���t�@�l�ō폜����

	const CVector3 SELECT_POS = { 0.0f,200.0f,0.0f };			//�Z���N�g�̈ʒu
	const CVector3 OK_POS = { 15.0f,-210.0f,0.0f };				//OK�̈ʒu
	const CVector3 STAGE_ZERO_POS = { -100.0f,0.0f,0.0f };		//�O�̈ʒu
	const CVector3 STAGE_ONE_POS = { 100.0f,0.0f,0.0f };		//�P�̈ʒu
	const CVector3 LEFT_TRIANGLE_POS = { -200.0f,0.0f,0.0f };	//���O�p�̈ʒu
	const CVector3 RIGHT_TRIANGLE_POS = { 200.0f,0.0f,0.0f };	//�E�O�p�̈ʒu
	const CVector3 UP_TRIANGLE_POS = { 0.0f,-100.0f,0.0f };		//��O�p�̈ʒu
	const CVector3 DOWN_TRIANGLE_POS = { 0.0f,-150.0f,0.0f };	//���O�p�̈ʒu
}

StageSelect::StageSelect()
{
	//������
	Init();
}


StageSelect::~StageSelect()
{
}

void StageSelect::Update()
{
}

void StageSelect::NewUpdate()
{

	g_gameData.SetStageNo(stageNo);
	if (!m_isOK) {
		//�Z���N�g��OK����I�����鏈��
		if (g_pad[0].IsTrigger(enButtonUp)) {
			m_selectNo--;
		}
		if (g_pad[0].IsTrigger(enButtonDown)) {
			m_selectNo++;
		}
		if (m_selectNo < 0) {
			m_selectNo = SELECT_NUM;
		}
		if (m_selectNo > SELECT_NUM) {
			m_selectNo = 0;
		}
		if (g_pad[0].IsTrigger(enButtonA)) {
			m_selectNo = enSelect_ok;
		}
		//�X�e�[�W��I�����鏈��
		if (m_selectNo == enSelect_stage) {
			//�����邩�����Ȃ���
			m_sprite[enSprite_upTriangle].SetAlpha(ALPHA_PLUS);
			m_sprite[enSprite_leftTriangle].SetAlpha(ALPHA_PLUS);
			m_sprite[enSprite_rightTriangle].SetAlpha(ALPHA_PLUS);
			m_sprite[enSprite_downTriangle].SetAlpha(TOUMEI_ALPHA);
			m_sprite[enSprite_ok].SetAlpha(TOUMEI_ALPHA);
			//�I��
			if (g_pad[0].IsTrigger(enButtonRight)) {
				stageNo++;
			}
			if (g_pad[0].IsTrigger(enButtonLeft)) {
				stageNo--;
			}
		}
	}
	//OK����A�{�^���ŃQ�[���ɑJ��
	if (m_selectNo == enSelect_ok) {
		//�����邩�����Ȃ���
		m_sprite[enSprite_leftTriangle].SetAlpha(TOUMEI_ALPHA);
		m_sprite[enSprite_rightTriangle].SetAlpha(TOUMEI_ALPHA);
		m_sprite[enSprite_downTriangle].SetAlpha(ALPHA_PLUS);
		m_sprite[enSprite_upTriangle].SetAlpha(TOUMEI_ALPHA);
		m_sprite[enSprite_ok].SetAlpha(ALPHA_PLUS);
		if (!m_isGame) {
			if (g_pad[0].IsTrigger(enButtonA)) {
				m_isOK = true;
				if (m_fade == nullptr) {
					m_fade = g_goMgr.NewGameObject<Fade>("fade");
					//�Q�[����
					m_isGame = true;
				}
			}
		}
	}
	//B�{�^���Ń^�C�g���ɖ߂�
	if (!m_isTitle) {
		if (g_pad[0].IsTrigger(enButtonB)) {
			m_isOK = true;
			if (m_fade == nullptr) {
				m_fade = g_goMgr.NewGameObject<Fade>("fade");
				//�^�C�g����
				m_isTitle = true;
			}
		}
	}
	//�I������ĂȂ������甼�����ɂ��鏈��
	for (int i = 0; i < g_gameData.enStage_Num; i++) {
		if (stageNo == i) {
			m_stageSprite[i].DeltaAlpha(ALPHA_PLUS);
		}
		else {
			m_stageSprite[i].SetAlpha(TOUMEI_ALPHA);
		}
	}
	if (stageNo < 0) {
		stageNo = STAGE_NUM;
	}
	if (stageNo > STAGE_NUM) {
		stageNo = 0;
	}
	//�Q�[���֑J��
	if (m_isGame) {
		if (m_fade->GetAlpha() >= DELETE_THIS_ALPHA) {
			g_goMgr.NewGameObject<Game>("game");
			g_goMgr.DeleteGameObject(this);
		}
	}
	//�^�C�g���֑J��
	if (m_isTitle) {
		if (m_fade->GetAlpha() >= DELETE_THIS_ALPHA) {
			g_goMgr.NewGameObject<Title>(0);
			g_goMgr.DeleteGameObject(this);
		}
	}
	//�X�V
	for (int i = 0; i < enSprite_Num; i++) {
		m_sprite[i].UpdateWorldMatrix(m_position[i], m_rotation, m_scale);
	}
	for (int i = 0; i < g_gameData.enStage_Num; i++) {
		m_stageSprite[i].UpdateWorldMatrix(m_stagePos[i], m_rotation, m_scale);
	}

}
void StageSelect::Draw2D()
{
	CMatrix mView;
	CMatrix mProj;
	mView.MakeLookAt(
		CAMERA_POSITION,
		CAMERA_TARGET,
		CAMERA_UP
	);
	mProj.MakeOrthoProjectionMatrix(VIEW_BOLUME_WIDTH, VIEW_BOLUME_HIGHT, F_NEAR, F_FAR);
	for (int i = 0; i < enSprite_Num; i++) {
		m_sprite[i].Draw(mView, mProj);
	}
	for (int i = 0; i < g_gameData.enStage_Num; i++) {
		m_stageSprite[i].Draw(mView, mProj);
	}
}
void StageSelect::Init()
{
	//�w�i
	m_sprite[enSprite_back].Init(L"Assets/sprite/back.dds", BACK_WIDTH, BACK_HIGHT);
	m_position[enSprite_back] = CVector3::Zero();
	//�Z���N�g
	m_sprite[enSprite_select].Init(L"Assets/sprite/select.dds", SELECT_WIDTH, SELECT_HIGHT);
	m_position[enSprite_select] = SELECT_POS;
	//OK
	m_sprite[enSprite_ok].Init(L"Assets/sprite/ok.dds", OK_WIDTH, OK_HIGHT);
	m_position[enSprite_ok] = OK_POS;
	//����
	m_sprite[enSprite_leftTriangle].Init(L"Assets/sprite/left_triangle.dds", LEFT_TRIANGLE_WIDTH, LEFT_TRIANGLE_HIGHT);
	m_position[enSprite_leftTriangle] = LEFT_TRIANGLE_POS;
	//�E��
	m_sprite[enSprite_rightTriangle].Init(L"Assets/sprite/right_triangle.dds", RIGHT_TRIANGLE_WIDTH, RIGHT_TRIANGLE_HIGHT);
	m_position[enSprite_rightTriangle] = RIGHT_TRIANGLE_POS;
	//�ぢ
	m_sprite[enSprite_upTriangle].Init(L"Assets/sprite/up_triangle.dds", UP_TRIANGLE_WIDTH, UP_TRIANGLE_HIGHT);
	m_position[enSprite_upTriangle] = UP_TRIANGLE_POS;
	//����
	m_sprite[enSprite_downTriangle].Init(L"Assets/sprite/down_triangle.dds", DOWN_TRIANGLE_WIDTH, DOWN_TRIANGLE_HIGHT);
	m_position[enSprite_downTriangle] = DOWN_TRIANGLE_POS;
	//�P
	m_stageSprite[g_gameData.enStage_Zero].Init(L"Assets/sprite/white_one.dds", STAGE_ZERO_WIDTH, STAGE_ZERO_HIGHT);
	m_stagePos[g_gameData.enStage_Zero] = STAGE_ZERO_POS;
	//�Q
	m_stageSprite[g_gameData.enStage_One].Init(L"Assets/sprite/white_two.dds", STAGE_ONE_WIDTH, STAGE_ONE_HIGHT);
	m_stagePos[g_gameData.enStage_One] = STAGE_ONE_POS;
}