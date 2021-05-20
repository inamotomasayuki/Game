#pragma once
#include "../UI/Fade.h"
#include "GameData.h"
class StageSelect final : public IGameObject
{
public:
	StageSelect();
	~StageSelect();
	/*
	* @brieef �X�V
	*/
	void Update() override;
	/*
	* @brieef �I�u�W�F�N�g����������X�V
	*/
	void NewUpdate() override;
	/*
	* @brieef �`��
	*/
	void Draw() override {}
	/*
	* @brieef 2D�`��
	*/
	void Draw2D() override;
private:
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/*
	* @enum EnSprite
	*�@�X�v���C�g�̎��
	*/
	enum EnSprite	{
		enSprite_back,			//�w�i
		enSprite_select,		//�Z���N�g	
		enSprite_ok,			//OK
		enSprite_leftTriangle,	//���O�p
		enSprite_rightTriangle,	//�E�O�p
		enSprite_upTriangle,	//��O�p
		enSprite_downTriangle,	//���O�p
		enSprite_Num			//��
	};
	/*
	* @enum EnSelect
	*  �I���̎��
	*/
	enum EnSelect
	{
		enSelect_stage,		//�X�e�[�W�Z���N�g��
		enSelect_ok,		//OK��
		enSelect_Num		//��
	};
	Sprite m_sprite[enSprite_Num];						//�X�v���C�g
	Sprite m_stageSprite[g_gameData.enStage_Num];		//�X�v���C�g
	CVector3 m_position[enSprite_Num];					//�ʒu
	CVector3 m_stagePos[g_gameData.enStage_Num];		//�ʒu
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�X�P�[��	
	Fade* m_fade = nullptr;								//�t�F�[�h
	int stageNo = g_gameData.GetStageNo();				//���݂̃X�e�[�W�̔ԍ��B
	int m_selectNo = 0;									//�Z���N�g�̐�
	bool m_isGame = false;								//�Q�[���ɂ�����
	bool m_isTitle = false;								//�^�C�g���ɂ�����
	bool m_isGo = false;								//�s���邩�ǂ���
	bool m_isOK = false;								//����
};