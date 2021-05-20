#pragma once
#include "graphics/2D/Sprite.h"

class Game;
class SpriteUI final : public IGameObject
{
public:
	SpriteUI();
	~SpriteUI();
	/*
	* @brieef �X�V
	*/
	void Update() override;
	/*
	* @brieef �`��
	*/
	void Draw() override {}
	/*
	* @brief 2D�`��
	*/
	void Draw2D() override;
	/*
	* @enum EnSpriteUI
	* �X�v���C�gUI�̎��
	*/
	enum EnSpriteUI {
		enSpriteUI_unityChan,		//���j�e�B�����
		enSpriteUI_kakeru,			//�~
		enSpriteUI_coin,			//�R�C��
		enSpriteUI_Num
	};
	/*
	* @enum EnSpriteScore
	* �X�R�A�p�̃X�v���C�g
	*/
	enum EnSpriteScore {
		enSpriteScore_zero,		//�X�R�A0
		enSpriteScore_one,		//�X�R�A1
		enSpriteScore_two,		//�X�R�A2
		enSpriteScore_three,	//�X�R�A3
		enSpriteScore_four,		//�X�R�A4
		enSpriteScore_five,		//�X�R�A5
		enSpriteScore_six,		//�X�R�A6
		enSpriteScore_seven,	//�X�R�A7
		enSpriteScore_eight,	//�X�R�A8
		enSpriteScore_nine,		//�X�R�A9
		enSpriteScore_Num		//��
	};
	/*
	* @enum EnSpriteHP
	* HP�p�̃X�v���C�g
	*/
	enum EnSpriteHP {
		enSpriteHP_zero,		//HP0
		enSpriteHP_one,			//HP1
		enSpriteHP_two,			//HP2
		enSpriteHP_three,		//HP3
		enSpriteHP_four,		//HP4
		enSpriteHP_five,		//HP5
		enSpriteHP_Num			//��
	};
private:
	Sprite m_spriteUI[enSpriteUI_Num];			//UI�X�v���C�g
	Sprite m_spriteScoreUI[enSpriteScore_Num];	//�X�R�A�X�v���C�g
	Sprite m_spriteScoreUI2[enSpriteScore_Num];	//�X�R�A�X�v���C�g
	Sprite m_spriteScoreUI3[enSpriteScore_Num];	//�X�R�A�X�v���C�g
	Sprite m_spriteHP[enSpriteHP_Num];			//HP�X�v���C�g
	CVector3 m_positionUI[enSpriteUI_Num];		//UI�ʒu
	CVector3 m_positionScoreUI;					//�X�R�A�ʒu
	CVector3 m_positionScoreUI2;				//�X�R�A�Q�ʒu
	CVector3 m_positionScoreUI3;				//�X�R�A�R�ʒu
	CVector3 m_positionHP;						//HP�ʒu
	CQuaternion m_rotation = CQuaternion::Identity();		//��]
	CVector3 m_scale = CVector3::One();						//�X�P�[��
	Game* m_game = nullptr;			//�Q�[��
	bool m_isHpUp = true;			//HP�A�b�v�ł��邩�ǂ���
};