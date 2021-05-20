#pragma once
#include "sound/SoundSource.h"
#include "IUIObject.h"
class UISound final: public IUIObject
{
public:
	UISound();
	~UISound();
	/*!
	* @brief 更新
	*/
	void Update() override;
private:
	/*!
	* @enum EnSE
	* 効果音の種類
	*/
	enum EnSE {
		enSE_cursor0,		//カーソル０
		enSE_decision,		//決定
		enSE_cancel,		//キャンセル
		enSE_adjustment,	//調整
		enSE_Num			//数
	};
	CSoundSource* m_se[enSE_Num] = { nullptr };		//効果音
};

