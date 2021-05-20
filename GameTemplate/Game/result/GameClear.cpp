#include "stdafx.h"
#include "GameClear.h"
namespace {
	const float VIEW_BOLUME_WIDTH = 1280.0f;			//�r���[�{�����[���̕�
	const float VIEW_BOLUME_HIGHT = 720.0f;				//�r���[�{�����[���̍���
	const float F_NEAR = 0.1f;							//�ߕ���
	const float F_FAR = 100.0f;							//������

	const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//�J�����̈ʒu
	const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//�J�����̒����_
	const CVector3 CAMERA_UP = { 0,1,0 };				//�J�����̏����

	const float ALPHA_PULS = 0.01f;						//alpha�l���Z
	const float ALPHA_MINUS = -0.01f;					//alpha�l���Z
	const float ALPHA_UPPER = 0.1f;						//alpha�l���
	const float ALPHA_LOWER = -0.1f;					//alpha�l����

	const float SPRITE_GAMECLEAR_WIDTH = 80.0f;					//�Q�[���I�[�o�[�摜�̕�
	const float SPRITE_GAMECLEAR_HIGHT = 45.0f;					//�Q�[���I�[�o�[�摜�̍���
	const float SPRITE_GAMECLEAR_SCALE = 16.0f;					//�Q�[���I�[�o�[�摜�̔{��
	const CVector3 SPRITE_GAMECLEAR_POS = CVector3::Zero();		//�Q�[���I�[�o�[�摜�̈ʒu

	const CVector3 SPRITE_SCALE = CVector3::One();		//�摜�̃X�P�[��
	const float SCALE_EXPANSION = 1.07f;				//�X�P�[���g��

	const float SPRITE_BUTTON_WIDTH = 960.0f;					//�{�^���摜�̕�	
	const float SPRITE_BUTTON_HIGHT = 540.0f;					//�{�^���摜�̍���
	const CVector3 SPRITE_BUTTON_POS = { 0.0f,-200.0f,0.0f };	//�{�^���摜�̈ʒu
	const float SPRITE_BUTTON_DELTA_ALPHA = -1.0f;				//�{�^���摜�̃A���t�@���Z

	const int SCALE_UP_DOWN_TIMER = 20;				//�X�P�[���g��k���^�C�}�[
	const float EXPANSION = 1.01f;					//�g��
	const float REDUCTION = 0.9901f;				//�k��
}
GameClear::GameClear()
{
	m_sprite[enSprite_clear].Init(L"Assets/sprite/gameClear.dds", SPRITE_GAMECLEAR_WIDTH, SPRITE_GAMECLEAR_HIGHT);
	m_position[enSprite_clear] = SPRITE_GAMECLEAR_POS;
	m_sprite[enSprite_button].Init(L"Assets/sprite/pressA.dds", SPRITE_BUTTON_WIDTH, SPRITE_BUTTON_HIGHT);
	m_position[enSprite_button] = SPRITE_BUTTON_POS;
	m_sprite[enSprite_button].DeltaAlpha(SPRITE_BUTTON_DELTA_ALPHA);
	for (int i = 0; i < enSprite_Num; i++) {
		m_scale[i] = SPRITE_SCALE;
	}

}


GameClear::~GameClear()
{
}

void GameClear::Update()
{
	if (!m_buttonFlag) {
		//�X�P�[�����g�傷��
		m_scale[enSprite_clear] *= SCALE_EXPANSION;
		//���ȏ�傫���Ȃ�����X�P�[�����Œ肷��
		if (m_scale[enSprite_clear].Length() >= CVector3::One().Length() * SPRITE_GAMECLEAR_SCALE) {
			m_scale[enSprite_clear] = CVector3::One() * SPRITE_GAMECLEAR_SCALE;
			m_buttonFlag = true;
		}
	}
	else {
		//�_�ł�����
		if (m_alphaState == enAlphaState_kieru) {
			m_buttonAlpha += ALPHA_MINUS;
			m_sprite[enSprite_button].DeltaAlpha(m_buttonAlpha);
			if (m_buttonAlpha <= ALPHA_LOWER)
			{
				m_alphaState = enAlphaState_kokunaru;
			}
		}
		if (m_alphaState == enAlphaState_kokunaru) {
			m_buttonAlpha += ALPHA_PULS;
			m_sprite[enSprite_button].DeltaAlpha(m_buttonAlpha);
			if (m_buttonAlpha >= ALPHA_UPPER)
			{
				m_alphaState = enAlphaState_kieru;
			}
		}
		//�g��k��������
		if (m_scaleState == enScaleState_up) {	
			m_scaleTimer++;
			m_scale[enSprite_clear] *= EXPANSION;
			if (m_scaleTimer == SCALE_UP_DOWN_TIMER) {
				m_scaleTimer = 0;
				m_scaleState = enScaleState_down;
			}
		}
		if (m_scaleState == enScaleState_down) {
			m_scaleTimer++;
			m_scale[enSprite_clear] *= REDUCTION;
			if (m_scaleTimer == SCALE_UP_DOWN_TIMER) {
				m_scaleTimer = 0;
				m_scaleState = enScaleState_up;
			}
		}
	}
	//�X�V
	for (int i = 0; i < enSprite_Num; i++) {
		m_sprite[i].UpdateWorldMatrix(m_position[i], m_rotation, m_scale[i]);
	}
}

void GameClear::Draw2D()
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
	for (int i = 0; i < enSprite_Num; i++) {
		m_sprite[i].Draw(mView, mProj);
	}
}