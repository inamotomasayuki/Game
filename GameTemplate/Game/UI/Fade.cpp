#include "stdafx.h"
#include "Fade.h"

namespace {
	const float SPRITE_WIDTH = 1280.0f;						//�X�v���C�g�̕�
	const float SPRITE_HIGHT = 720.0f;						//�X�v���C�g�̍���
	const float VIEW_BOLUME_WIDTH = 1280.0f;		//�r���[�{�����[���̕�
	const float VIEW_BOLUME_HIGHT = 720.0f;			//�r���[�{�����[���̍���
	const float F_NEAR = 0.1f;						//�ߕ���
	const float F_FAR = 100.0f;						//������

	const int FADEOUT_TIMER = 15;					//�t�F�[�h�A�E�g�܂ł̎���

	const float MINUS_ALPHA = -0.02f;				//�A���t�@�l�}�C�i�X
	const float PLUS_ALPHA = 0.02f;					//�A���t�@�l�v���X
	const float MINUS_START_ALPHA = 1.0f;			//�}�C�i�X���J�n����A���t�@�l
	const float INIT_ALPHA = -0.1f;					//�A���t�@�����l

	const float UPPER_ALPHA = 1.0f;					//�A���t�@�l���
	const float DELETE_ALPHA = 0.0f;				//���̃A���t�@�l�ō폜����

	const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//�J�����̈ʒu
	const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//�J�����̒����_
	const CVector3 CAMERA_UP = { 0,1,0 };				//�J�����̏����
}

Fade::Fade()
{
	m_sprite.Init(L"Assets/sprite/black.dds", SPRITE_WIDTH, SPRITE_HIGHT);
	m_sprite.SetAlpha(INIT_ALPHA);
}


Fade::~Fade()
{
}

void Fade::Update()
{
	if (!m_isFade) {
		//�Â�����
		m_sprite.DeltaAlpha(PLUS_ALPHA);
		if (m_sprite.GetAlpha() >= UPPER_ALPHA) {
			m_timer++;
		}
	}
	if (m_timer >= FADEOUT_TIMER) {
		m_isFade = true;
	}
	if (m_isFade) {
		//��������
		m_sprite.DeltaAlpha(MINUS_ALPHA);
		if (m_sprite.GetAlpha() <= DELETE_ALPHA) {
			//�폜
			g_goMgr.DeleteGameObject(this);
		}
	}
	m_sprite.UpdateWorldMatrix(m_spritePos, m_spriteRot, m_spriteScale);
}

void Fade::DrawFade()
{
	CMatrix mView;
	CMatrix mProj;
	mView.MakeLookAt(
		CAMERA_POSITION,
		CAMERA_TARGET,
		CAMERA_UP
	);
	mProj.MakeOrthoProjectionMatrix(VIEW_BOLUME_WIDTH, VIEW_BOLUME_HIGHT, F_NEAR, F_FAR);

	//�`��
	m_sprite.Draw(mView, mProj);

}
