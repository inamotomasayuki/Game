#pragma once
#include "graphics/2D/Sprite.h"
#include "player/Player.h"
class Game;

class GameOver final : public IGameObject
{
public:
	GameOver();
	~GameOver();
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
	/// <summary>
	/// �{�^���\���t���O�̎擾
	/// </summary>
	/// <returns>�{�^���\���t���O</returns>
	bool GetButtonFlag()
	{
		return m_buttonFlag;
	}
	/*
	* @enum EnSprite
	* �X�v���C�g�̎��
	*/
	enum EnSprite {
		enSprite_gameOver,		//�Q�[���I�[�o�[
		enSprite_button,		//�{�^��
		enSprite_Num			//�X�v���C�g�̐�
	};
private:
	Sprite m_sprite[enSprite_Num];			//�X�v���C�g
	CVector3 m_position[enSprite_Num];		//�ʒu
	CQuaternion m_rotation[enSprite_Num];	//��]
	CVector3 m_scale[enSprite_Num];			//�g�嗦
	Player* m_player = nullptr;				//�v���C���[
	/// <summary>
	/// �A���t�@�l�X�e�[�g
	/// </summary>
	enum EnState
	{
		enState_kieru,			//������
		enState_kokunaru		//�Z���Ȃ�
	};
	EnState m_state = enState_kokunaru;		//alpha�X�e�[�g
	float m_rotSpeed = -15.0f;				//��]���x
	float m_rotCount = 0;					//��]�J�E���g
	float m_buttonAlpha = 0.1f;				//�{�^����alpha�l
	bool m_buttonFlag = false;				//�_�Ńt���O

};

