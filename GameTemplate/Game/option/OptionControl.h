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
	* @brief 更新
	*/
	void Update() override;
private:
	UIData* m_uiData = nullptr;				//UIでーた　
	OptionData* m_optionData = nullptr;		//オプションデータ
	bool m_isTriggerRight = false;			//右トリガー？
	bool m_isPressRight = false;			//右プレス？
	int m_timerRight = 0;					//右タイマー
	bool m_isTriggerLeft = false;			//左トリガー？
	bool m_isPressLeft = false;				//左プレス？
	int m_timerLeft = 0;					//左タイマー
	CSoundSource* m_se = nullptr;			//効果音
};

