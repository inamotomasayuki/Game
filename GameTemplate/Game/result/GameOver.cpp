#include "stdafx.h"
#include "GameOver.h"
namespace {
	const float VIEW_BOLUME_WIDTH = 1280.0f;		//�r���[�{�����[���̕�
	const float VIEW_BOLUME_HIGHT = 720.0f;			//�r���[�{�����[���̍���
	const float F_NEAR = 0.1f;						//�ߕ���
	const float F_FAR = 100.0f;						//������

	const float SPRITE_GAMEOVER_WIDTH = 80.0f;				//�Q�[���I�[�o�[�摜�̕�
	const float SPRITE_GAMEOVER_HIGHT = 45.0f;				//�Q�[���I�[�o�[�摜�̍���
	const float SPRITE_GAMEOVER_SCALE = 16.0f;				//�Q�[���I�[�o�[�摜�̔{��
	const CVector3 SPRITE_GAMEOVER_POS = CVector3::Zero();	//�Q�[���I�[�o�[�摜�̈ʒu

	const CVector3 SPRITE_SCALE = CVector3::One();			//�摜�̃X�P�[��
	const CQuaternion SPRITE_ROT = CQuaternion::Identity();	//�摜�̉�]

	const float SPRITE_BUTTON_WIDTH = 960.0f;					//�{�^���摜�̕�	
	const float SPRITE_BUTTON_HIGHT = 540.0f;					//�{�^���摜�̍���
	const CVector3 SPRITE_BUTTON_POS = { 0.0f,-200.0f,0.0f };	//�{�^���摜�̈ʒu
	const float SPRITE_BUTTON_DELTA_ALPHA = -1.0f;				//�{�^���摜�̃A���t�@���Z

	const CVector3 CAMERA_POSITION = { 0, 0, -1 };		//�J�����̈ʒu
	const CVector3 CAMERA_TARGET = { 0, 0, 0 };			//�J�����̒����_
	const CVector3 CAMERA_UP = { 0,1,0 };				//�J�����̏����

	const float SCALE_EXPANSION = 1.07f;			//�X�P�[���g��

	const float ROTATION_NUM = -720.0f;		//��]

	const float ALPHA_PULS = 0.01f;				//alpha�l���Z
	const float ALPHA_MINUS = -0.01f;			//alpha�l���Z
	const float ALPHA_UPPER = 0.1f;				//alpha�l���
	const float ALPHA_LOWER = -0.1f;			//alpha�l����
}
GameOver::GameOver()
{
	m_sprite[enSprite_gameOver].Init(L"Assets/sprite/gameOver.dds", SPRITE_GAMEOVER_WIDTH, SPRITE_GAMEOVER_HIGHT);
	m_position[enSprite_gameOver] = SPRITE_GAMEOVER_POS;
	m_sprite[enSprite_button].Init(L"Assets/sprite/pressA.dds", SPRITE_BUTTON_WIDTH, SPRITE_BUTTON_HIGHT);
	m_position[enSprite_button] = SPRITE_BUTTON_POS;
	m_sprite[enSprite_button].DeltaAlpha(SPRITE_BUTTON_DELTA_ALPHA);
	for (int i = 0; i < enSprite_Num; i++) {
		m_rotation[i] = SPRITE_ROT;
		m_scale[i] = SPRITE_SCALE;
	}
}


GameOver::~GameOver()
{
}

void GameOver::Update()
{
	m_player = g_goMgr.FindGameObject<Player>("player");
	//�X�P�[�����g�傷��
	m_scale[enSprite_gameOver] *= SCALE_EXPANSION;
	//���ȏ�傫���Ȃ�����X�P�[�����Œ肷��
	if (m_scale[enSprite_gameOver].Length() > CVector3::One().Length() * SPRITE_GAMEOVER_SCALE) {
		m_scale[enSprite_gameOver] = CVector3::One() * SPRITE_GAMEOVER_SCALE;
	}
	//��]
	CQuaternion addRot;
	m_rotCount += m_rotSpeed;
	//����]������~�߂�
	if (m_rotCount < ROTATION_NUM) {
		m_rotSpeed = 0;
		m_buttonFlag = true;
	}
	addRot.SetRotationDeg(CVector3::AxisZ(), m_rotSpeed);
	m_rotation[enSprite_gameOver].Multiply(addRot);
	//�t���O����������_�ł�����
	if (m_buttonFlag) {
		if (m_player != nullptr) {
			m_player->SetIsAttacked(false);
		}
		if (m_state == enState_kieru) {
			m_buttonAlpha += ALPHA_MINUS;
			m_sprite[enSprite_button].DeltaAlpha(m_buttonAlpha);
			if (m_buttonAlpha <= ALPHA_LOWER)
			{
				m_state = enState_kokunaru;
			}
		}
		if (m_state == enState_kokunaru) {
			m_buttonAlpha += ALPHA_PULS;
			m_sprite[enSprite_button].DeltaAlpha(m_buttonAlpha);
			if (m_buttonAlpha >= ALPHA_UPPER)
			{
				m_state = enState_kieru;
			}

		}
	}
	//�X�V
	for (int i = 0; i < enSprite_Num; i++) {
		m_sprite[i].UpdateWorldMatrix(m_position[i], m_rotation[i], m_scale[i]);
	}
}
void GameOver::Draw2D()
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
}