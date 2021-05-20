#pragma once
#include "UI/menu/IUIObject.h"
#include "OptionData.h"
#include "UI/menu/UIData.h"
#include "sound/SoundSource.h"
class OptionControl final : public IUIObject
{
public:
	OptionControl();
	~OptionControl();
	/*
	* @brief �X�V
	*/
	void Update() override;
private:
	UIData* m_uiData = nullptr;				//UI�Ł[���@
	OptionData* m_optionData = nullptr;		//�I�v�V�����f�[�^
	bool m_isTriggerRight = false;			//�E�g���K�[�H
	bool m_isPressRight = false;			//�E�v���X�H
	int m_timerRight = 0;					//�E�^�C�}�[
	bool m_isTriggerLeft = false;			//���g���K�[�H
	bool m_isPressLeft = false;				//���v���X�H
	int m_timerLeft = 0;					//���^�C�}�[
	CSoundSource* m_se = nullptr;			//���ʉ�
};

