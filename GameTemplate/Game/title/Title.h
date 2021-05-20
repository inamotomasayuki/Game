#pragma once
#include "graphics/2D/Sprite.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "../UI/Fade.h"

class Title final : public IGameObject
{
public:
	Title();
	~Title();
	/*
	* @brief �X�V
	*/
	void Update() override {};
	/*
	* @brief ��������������X�V
	*/
	void NewUpdate() override;
	/*
	* @brief �`��
	*/
	void Draw() override {}
	/*
	* @brief 2D�`��
	*/
	void Draw2D() override;
private:
	/*!
	* @enum EnSprite
	* �X�v���C�g�̎��
	*/
	enum EnSprite
	{
		enSprite_back,		//�w�i
		enSprite_title,		//�^�C�g��
		enSprite_start,		//�X�^�[�g	
		enSprite_Num		//��
	};
	Sprite m_sprite[enSprite_Num];		//�X�v���C�g
	Sprite m_kariSprite;				//���X�v���C�g
	CSoundSource* m_bgm = nullptr;		//BGM
	CVector3 m_position[enSprite_Num];	//�ʒu
	CVector3 m_kariPos;					//���ʒu
	CQuaternion m_rotation = CQuaternion::Identity();		//��]
	CQuaternion m_backRot = CQuaternion::Identity();		//�w�i��]
	CQuaternion m_startRot = CQuaternion::Identity();		//�X�^�[�g��]
	CVector3 m_scale = CVector3::One();						//�X�P�[��
	CVector3 m_kariScale;					//���X�P�[��
	Fade* m_fade = nullptr;					//�t�F�[�h�C��
	int m_timer = 0;						//�^�C�}�[
	bool m_isKari = false;					//���\���H
	bool m_isStart = false;					//�X�^�[�g�\���H
	bool m_isSelect = false;				//�Z���N�g�ɂ�����
	bool m_isGo = false;					//�s���邩�ǂ���
};

