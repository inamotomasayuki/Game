#pragma once
#include "graphics/2D/Sprite.h" 
class GameClear final : public IGameObject
{
public:
	GameClear();
	~GameClear();
	/*!
	*@brief �X�V
	*/
	void Update() override;
	/*!
	*@brief �`��
	*/
	void Draw() override {};
	/*!
	*@brief 2D�`��
	*/
	void Draw2D() override;
	/*!
	* enum EnSprite
	*�@�X�v���C�g�̎��
	*/
	enum EnSprite {
		enSprite_clear,			//�N���A
		enSprite_button,		//�{�^��
		enSprite_Num			//�X�v���C�g�̐�
	};
private:
	/*!
	* enum EnAlphaState
	* �A���t�@�l�X�e�[�g
	*/
	enum EnAlphaState
	{
		enAlphaState_kieru,				//������
		enAlphaState_kokunaru			//�Z���Ȃ�
	};
	EnAlphaState m_alphaState = enAlphaState_kokunaru;		//alpha�X�e�[�g
	/*!
	* enum EnScaleState
	* �g�嗦�X�e�[�g
	*/
	enum EnScaleState
	{
		enScaleState_up,			//�g��
		enScaleState_down			//�k��
	};
	EnScaleState m_scaleState = enScaleState_up;		//�X�P�[���X�e�[�g
	Sprite m_sprite[enSprite_Num];						//�X�v���C�g
	CVector3 m_position[enSprite_Num];					//�ʒu
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale[enSprite_Num];						//�X�P�[��
	bool m_buttonFlag = false;							//�_�Ńt���O
	int m_scaleTimer = 0;								//�X�P�[���^�C�}�[�@�P�ʁF�b
	float m_buttonAlpha = 0.1f;							//�{�^����alpha�l
};

