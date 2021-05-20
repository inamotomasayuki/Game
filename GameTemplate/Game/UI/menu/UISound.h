#pragma once
#include "sound/SoundSource.h"
#include "IUIObject.h"
class UISound final: public IUIObject
{
public:
	UISound();
	~UISound();
	/*!
	* @brief �X�V
	*/
	void Update() override;
private:
	/*!
	* @enum EnSE
	* ���ʉ��̎��
	*/
	enum EnSE {
		enSE_cursor0,		//�J�[�\���O
		enSE_decision,		//����
		enSE_cancel,		//�L�����Z��
		enSE_adjustment,	//����
		enSE_Num			//��
	};
	CSoundSource* m_se[enSE_Num] = { nullptr };		//���ʉ�
};

