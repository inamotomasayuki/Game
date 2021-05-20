#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "../select/StageSelect.h"

namespace {
	const float VIEW_BOLUME_WIDTH = 1280.0f;		//�r���[�{�����[���̕�
	const float VIEW_BOLUME_HIGHT = 720.0f;			//�r���[�{�����[���̍���
	const float F_NEAR = 0.1f;						//�ߕ���
	const float F_FAR = 100.0f;						//������

	const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//�J�����̈ʒu
	const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//�J�����̒����_
	const CVector3 CAMERA_UP = { 0,1,0 };				//�J�����̏����

	const float ROT_SPEED = 5.0f;
	const int ROT_START_TIME = 120;				//��]�J�n����
	const int ROT_RETURN_TIME = 125;			//��]�߂鎞��
	const int ROT_END_TIME = 135;				//��]�I��莞��
	const float BACK_WIDTH = 1500.0f;			//�w�i�̕�
	const float BACK_HIGHT = 1500.0f;			//�w�i�̍���
	const float TITLE_WIDTH = 1280.0f;			//�^�C�g���̕�
	const float TITLE_HIGHT = 720.0f;			//�^�C�g���̍���
	const float KARI_WIDTH = 1280.0f;			//���̕�
	const float KARI_HIGHT = 720.0f;			//���̍���
	const float START_WIDTH = 1280.0f;			//�X�^�[�g�̕�
	const float START_HIGHT = 720.0f;			//�X�^�[�g�̍���
	const CVector3 BACK_POS = CVector3::Zero();				//�w�i�ʒu
	const CVector3 TITLE_POS = { 0.0f,500.0f,0.0f };		//�^�C�g���ʒu
	const CVector3 START_POS = { 0.0f,-200.0f,0.0f };		//�X�^�[�g�ʒu
	const CVector3 KARI_SCALE = { 10.0f,10.0f,10.0f };		//���ʒu
	const float TITLE_Y_POS = 200.0f;						//�ŏI�I�ȃ^�C�g����Y�ʒu
	const float TITLE_DOWN_SPEED = 5.0f;					//�^�C�g��������Ă���X�s�[�h
	const float ALPHA_MINUS = -1.0f;						//�A���t�@�l�}�C�i�X
	const float ALPHA_PLUS = 1.0f;							//�A���t�@�l�v���X
	const float DELTA_ALPHA = 0.1f;							//���X�ɃA���t�@
	const float BACK_ROT_SPEED = -0.1f;						//�w�i��]���x
	const float KARI_SCALE_REDUCTION = 0.93f;				//���k���X�s�[�h
	const float DELETE_THIS_ALPHA = 1.0f;			//�t�F�[�h�����̃A���t�@�l�ō폜����
}
Title::Title()
{
	m_sprite[enSprite_back].Init(L"Assets/sprite/back.dds", BACK_WIDTH, BACK_HIGHT);
	m_position[enSprite_back] = BACK_POS;
	m_sprite[enSprite_title].Init(L"Assets/sprite/TitleMoji.dds", TITLE_WIDTH, TITLE_HIGHT);
	m_position[enSprite_title] = TITLE_POS;
	m_sprite[enSprite_start].Init(L"Assets/sprite/start.dds", START_WIDTH, START_HIGHT);
	m_position[enSprite_start] = START_POS;
	m_kariSprite.Init(L"Assets/sprite/kari.dds", KARI_WIDTH, KARI_HIGHT);
	m_kariPos = CVector3::Zero();
	m_kariScale = KARI_SCALE;
	m_bgm = g_goMgr.NewGameObject<CSoundSource>(0);
	m_bgm->Init(L"Assets/sound/title.wav");
	m_bgm->Play(true);
}


Title::~Title()
{
	g_goMgr.DeleteGameObject(m_bgm);
}


void Title::NewUpdate()
{
	//�^�C�g������Ă��鏈��
	if (m_position[enSprite_title].y == TITLE_Y_POS) {
		m_position[enSprite_title].y = TITLE_Y_POS;
		m_isKari = true;
	}
	else {
		m_position[enSprite_title].y -= TITLE_DOWN_SPEED;
	}
	//�����{���Əo������
	if (!m_isKari) {
		m_kariSprite.SetAlpha(ALPHA_MINUS);
	}
	else {
		m_kariSprite.SetAlpha(ALPHA_PLUS);
		m_kariScale *= KARI_SCALE_REDUCTION;
		if (m_kariScale.x <= CVector3::One().x) {
			m_kariScale = CVector3::One();
			m_isStart = true;
		}
	}
	//�X�^�[�g���ӂ���Əo������
	if (!m_isStart) {
		m_sprite[enSprite_start].SetAlpha(ALPHA_MINUS);
	}
	else {
		m_sprite[enSprite_start].DeltaAlpha(DELTA_ALPHA);
		//�J��
		if (g_pad[0].IsTrigger(enButtonA)) {
			if (m_fade == nullptr) {
				m_fade = g_goMgr.NewGameObject<Fade>("fade");
				m_isSelect = true;
			}
		}
	}
	if (m_isSelect) {
		if (m_fade->GetAlpha() >= DELETE_THIS_ALPHA) {
			g_goMgr.NewGameObject<StageSelect>(0);
			g_goMgr.DeleteGameObject(this);
		}
	}
	CQuaternion addRot;
	float rotSpeed;
	//�X�V
	for (int i = 0; i < enSprite_Num; i++) {
		if (i == enSprite_back) {
			rotSpeed = BACK_ROT_SPEED;
			addRot.SetRotationDeg(CVector3::AxisZ(), rotSpeed);
			m_backRot.Multiply(addRot);
			m_sprite[i].UpdateWorldMatrix(m_position[i], m_backRot, m_scale);
		}
		//�X�^�[�g��]
		else if (i == enSprite_start) {
			m_timer++;
			if (m_timer >= ROT_START_TIME && m_timer <= ROT_RETURN_TIME) {
				rotSpeed = -ROT_SPEED;
			}
			else if (m_timer > ROT_RETURN_TIME && m_timer < ROT_END_TIME) {
				rotSpeed = ROT_SPEED;
			}
			else if (m_timer == ROT_END_TIME) {
				m_timer = 0;
			}
			else {
				rotSpeed = 0.0f;
				m_startRot = CQuaternion::Identity();
			}
			addRot.SetRotationDeg(CVector3::AxisZ(), rotSpeed);
			m_startRot.Multiply(addRot);
			m_sprite[i].UpdateWorldMatrix(m_position[i], m_startRot, m_scale);
		}
		else {
			m_sprite[i].UpdateWorldMatrix(m_position[i], m_rotation, m_scale);
		}
	}
	m_kariSprite.UpdateWorldMatrix(m_kariPos, m_rotation, m_kariScale);
}
void Title::Draw2D()
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
	m_kariSprite.Draw(mView, mProj);
}
