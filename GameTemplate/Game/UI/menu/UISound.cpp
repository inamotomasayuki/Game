#include "stdafx.h"
#include "UISound.h"
#include "UIData.h"

UISound::UISound()
{
	for (int i = 0; i < enSE_Num; i++) {
		m_se[i] = g_goMgr.NewGameObject<CSoundSource>(0);
	}
	m_se[enSE_decision]->Init(L"Assets/sound/decision.wav");
	m_se[enSE_cursor0]->Init(L"Assets/sound/cursor.wav");
	m_se[enSE_cancel]->Init(L"Assets/sound/cancel.wav");
	m_se[enSE_adjustment]->Init(L"Assets/sound/select06.wav");
}


UISound::~UISound()
{
}

void UISound::Update()
{
	const auto& uiData = &GetUIData();
	if (uiData->GetPageState() < uiData->enPage_Num - 1
		&& uiData->GetOptionPageState() < uiData->enOptionPage_Num - 1) {
		//決定
		if (uiData->GetOptionListState() == uiData->enOptionList_bloom) {
			if (uiData->GetOptionPageState() == uiData->enOptionPage_two) {
				if (g_pad[0].IsTrigger(enButtonA)) {
					m_se[enSE_decision]->Stop();
					m_se[enSE_decision]->Play(false);
				}
			}
			if (uiData->GetBloomState() == uiData->enBloom_init) {
				if (g_pad[0].IsTrigger(enButtonA)) {
					m_se[enSE_decision]->Stop();
					m_se[enSE_decision]->Play(false);
				}
			}
		}
		if (uiData->GetOptionListState() == uiData->enOptionList_light) {
			if (uiData->GetLightState() == uiData->enLight_init
				|| uiData->GetLightState() == uiData->enLight_color) {
				if (g_pad[0].IsTrigger(enButtonA)) {
					m_se[enSE_decision]->Stop();
					m_se[enSE_decision]->Play(false);
				}
			}
		}
	}
	//調整
	if (uiData->GetOptionPageState() == uiData->enOptionPage_three) {
		if (uiData->GetOptionListState() == uiData->enOptionList_bloom) {
			if (uiData->GetBloomState() != uiData->enBloom_init) {
				if (g_pad[0].IsTrigger(enButtonLeft)) {
					m_se[enSE_adjustment]->Stop();
					m_se[enSE_adjustment]->Play(false);
				}
				if (g_pad[0].IsTrigger(enButtonRight)) {
					m_se[enSE_adjustment]->Stop();
					m_se[enSE_adjustment]->Play(false);
				}
			}
		}
		if (uiData->GetOptionListState() == uiData->enOptionList_light) {
			if (uiData->GetLightState() != uiData->enLight_init
				&& uiData->GetLightState() != uiData->enLight_color) {
				if (g_pad[0].IsTrigger(enButtonLeft)) {
					m_se[enSE_adjustment]->Stop();
					m_se[enSE_adjustment]->Play(false);
				}
				if (g_pad[0].IsTrigger(enButtonRight)) {
					m_se[enSE_adjustment]->Stop();
					m_se[enSE_adjustment]->Play(false);
				}
			}
		}
	}
	if (uiData->GetOptionPageState() == uiData->enOptionPage_four) {
		if (g_pad[0].IsTrigger(enButtonLeft)) {
			m_se[enSE_adjustment]->Stop();
			m_se[enSE_adjustment]->Play(false);
		}
		if (g_pad[0].IsTrigger(enButtonRight)) {
			m_se[enSE_adjustment]->Stop();
			m_se[enSE_adjustment]->Play(false);
		}
	}
	//キャンセル
	if (g_pad[0].IsTrigger(enButtonB)) {
		m_se[enSE_cancel]->Stop();
		m_se[enSE_cancel]->Play(false);
	}
	//カーソル１
	if (uiData->GetPageState() != uiData->enPage_three) {
		if (g_pad[0].IsTrigger(enButtonDown)) {
			m_se[enSE_cursor0]->Stop();
			m_se[enSE_cursor0]->Play(false);
		}
		if (g_pad[0].IsTrigger(enButtonUp)) {
			m_se[enSE_cursor0]->Stop();
			m_se[enSE_cursor0]->Play(false);
		}
	}
	if (uiData->GetPageState() == uiData->enPage_three) {
		if (g_pad[0].IsTrigger(enButtonRight)) {
			m_se[enSE_cursor0]->Stop();
			m_se[enSE_cursor0]->Play(false);
		}
		if (g_pad[0].IsTrigger(enButtonLeft)) {
			m_se[enSE_cursor0]->Stop();
			m_se[enSE_cursor0]->Play(false);
		}
	}
}