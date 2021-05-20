#include "stdafx.h"
#include "OptionControl.h"
namespace {
	const float POW = 0.0799f;
	const float RGB = 0.008f;
	const float BRIGHTNESS = 0.03f;
	const float SKY_BRIGHTNESS = 0.01f;
}
OptionControl::OptionControl()
{
	m_se = g_goMgr.NewGameObject<CSoundSource>(0);
	m_se->Init(L"Assets/sound/select06.wav");
	m_se->SetVolume(0.4f);
}


OptionControl::~OptionControl()
{
}

void OptionControl::Update()
{
	/*
	���͂����������Ă�ꍇ�A�P�v���X���Ă��炿����ƊԂ��J���ĘA���ŉ��Z�����悤�ɂ��Ă���B
	�X�}�[�g�ɂł��Ȃ��������ߏ������艟���R�[�h�ɂȂ��Ă��܂����B
	����Ă��邱�Ƃ̓X�e�[�g���ƂɑS�������ł���B
	*/
	m_optionData = &GetOptionData();
	m_uiData = &GetUIData();
	if (m_uiData->GetOptionPageState() == m_uiData->enOptionPage_three) {
		if (m_uiData->GetOptionListState() == m_uiData->enOptionList_bloom) {
			switch (m_uiData->GetBloomState()) {
			case UIData::Bloom::enBloom_luminance:
				//�u���[���̃s�N�Z���L������P�x�̑���
				if (g_pad[0].IsPress(enButtonRight)) {
					if (!m_isTriggerRight) {
						m_optionData->AddLuminance(-0.05f);
						m_isTriggerRight = true;
					}
					else {
						if (!m_isPressRight) {
							m_timerRight++;
							if (m_timerRight == 20) {
								m_isPressRight = true;
								m_timerRight = 0;
							}
						}
					}
					if (m_isPressRight) {
						m_se->Stop();
						m_se->Play(false);
						m_optionData->AddLuminance(-0.05f);
					}
				}
				else {
					m_isTriggerRight = false;
					m_isPressRight = false;
					m_timerRight = 0;
				}
				if (g_pad[0].IsPress(enButtonLeft)) {
					if (!m_isTriggerLeft) {
						m_optionData->AddLuminance(0.05f);
						m_isTriggerLeft = true;
					}
					else {
						if (!m_isPressLeft) {
							m_timerLeft++;
							if (m_timerLeft == 20) {
								m_isPressLeft = true;
								m_timerLeft = 0;
							}
						}
					}
					if (m_isPressLeft) {
						m_se->Stop();
						m_se->Play(false);
						m_optionData->AddLuminance(0.05f);
					}
				}
				else {
					m_isTriggerLeft = false;
					m_isPressLeft = false;
					m_timerLeft = 0;
				}
				break;
			case UIData::Bloom::enBloom_pow:
				//�u���[���̋����̑���
				if (g_pad[0].IsPress(enButtonRight)) {
					if (!m_isTriggerRight) {
						m_optionData->AddPow(-POW);
						m_isTriggerRight = true;
					}
					else {
						if (!m_isPressRight) {
							m_timerRight++;
							if (m_timerRight == 20) {
								m_isPressRight = true;
								m_timerRight = 0;
							}
						}
					}
					if (m_isPressRight) {
						m_se->Stop();
						m_se->Play(false);
						m_optionData->AddPow(-POW);
					}
				}
				else {
					m_isTriggerRight = false;
					m_isPressRight = false;
					m_timerRight = 0;
				}
				if (g_pad[0].IsPress(enButtonLeft)) {
					if (!m_isTriggerLeft) {
						m_optionData->AddPow(POW);
						m_isTriggerLeft = true;
					}
					else {
						if (!m_isPressLeft) {
							m_timerLeft++;
							if (m_timerLeft == 20) {
								m_isPressLeft = true;
								m_timerLeft = 0;
							}
						}
					}
					if (m_isPressLeft) {
						m_se->Stop();
						m_se->Play(false);
						m_optionData->AddPow(POW);
					}
				}
				else {
					m_isTriggerLeft = false;
					m_isPressLeft = false;
					m_timerLeft = 0;
				}
			case UIData::Bloom::enBloom_init:
				if (g_pad[0].IsTrigger(enButtonA)) {
					m_optionData->InitBloomParameter();
				}
				break;
			}
		}
		if (m_uiData->GetOptionListState() == m_uiData->enOptionList_light) {
			switch (m_uiData->GetLightState()) {
			case UIData::Light::enLight_brightness:
				//���C�g�̖��邳�̑���
				if (g_pad[0].IsPress(enButtonRight)) {
					if (!m_isTriggerRight) {
						m_optionData->AddBrightness(BRIGHTNESS);
						m_isTriggerRight = true;
					}
					else {
						if (!m_isPressRight) {
							m_timerRight++;
							if (m_timerRight == 20) {
								m_isPressRight = true;
								m_timerRight = 0;
							}
						}
					}
					if (m_isPressRight) {
						m_se->Stop();
						m_se->Play(false);
						m_optionData->AddBrightness(BRIGHTNESS);
					}
				}
				else {
					m_isTriggerRight = false;
					m_isPressRight = false;
					m_timerRight = 0;
				}
				if (g_pad[0].IsPress(enButtonLeft)) {
					if (!m_isTriggerLeft) {
						m_optionData->AddBrightness(-BRIGHTNESS);
						m_isTriggerLeft = true;
					}
					else {
						if (!m_isPressLeft) {
							m_timerLeft++;
							if (m_timerLeft == 20) {
								m_isPressLeft = true;
								m_timerLeft = 0;
							}
						}
					}
					if (m_isPressLeft) {
						m_se->Stop();
						m_se->Play(false);
						m_optionData->AddBrightness(-BRIGHTNESS);
					}
				}
				else {
					m_isTriggerLeft = false;
					m_isPressLeft = false;
					m_timerLeft = 0;
				}
				break;
			case UIData::Light::enLight_skyBrightness:
				//��̖��邳�̑���
				if (g_pad[0].IsPress(enButtonRight)) {
					if (!m_isTriggerRight) {
						m_optionData->AddSkyBrightness(SKY_BRIGHTNESS);
						m_isTriggerRight = true;
					}
					else {
						if (!m_isPressRight) {
							m_timerRight++;
							if (m_timerRight == 20) {
								m_isPressRight = true;
								m_timerRight = 0;
							}
						}
					}
					if (m_isPressRight) {
						m_se->Stop();
						m_se->Play(false);
						m_optionData->AddSkyBrightness(SKY_BRIGHTNESS);
					}
				}
				else {
					m_isTriggerRight = false;
					m_isPressRight = false;
					m_timerRight = 0;
				}
				if (g_pad[0].IsPress(enButtonLeft)) {
					if (!m_isTriggerLeft) {
						m_optionData->AddSkyBrightness(-SKY_BRIGHTNESS);
						m_isTriggerLeft = true;
					}
					else {
						if (!m_isPressLeft) {
							m_timerLeft++;
							if (m_timerLeft == 20) {
								m_isPressLeft = true;
								m_timerLeft = 0;
							}
						}
					}
					if (m_isPressLeft) {
						m_se->Stop();
						m_se->Play(false);
						m_optionData->AddSkyBrightness(-SKY_BRIGHTNESS);
					}
				}
				else {
					m_isTriggerLeft = false;
					m_isPressLeft = false;
					m_timerLeft = 0;
				}
				break;
			case UIData::Light::enLight_init:
				//����������
				if (g_pad[0].IsTrigger(enButtonA)) {
					m_optionData->InitLightParameter();
				}
				break;
			}
		}
	}
	if (m_uiData->GetOptionPageState() == m_uiData->enOptionPage_four) {
		//�f�B���N�V�������C�g�̃J���[�̑���
		switch (m_uiData->GetLightColorState()) {
		case UIData::LightColor::enLightColor_b:		//B
			if (g_pad[0].IsPress(enButtonRight)) {
				if (!m_isTriggerRight) {
					m_optionData->AddColorB(RGB);
					m_isTriggerRight = true;
				}
				else {
					if (!m_isPressRight) {
						m_timerRight++;
						if (m_timerRight == 20) {
							m_isPressRight = true;
							m_timerRight = 0;
						}
					}
				}
				if (m_isPressRight) {
					m_se->Stop();
					m_se->Play(false);
					m_optionData->AddColorB(RGB);
				}
			}
			else {
				m_isTriggerRight = false;
				m_isPressRight = false;
				m_timerRight = 0;
			}
			if (g_pad[0].IsPress(enButtonLeft)) {
				if (!m_isTriggerLeft) {
					m_optionData->AddColorB(-RGB);
					m_isTriggerLeft = true;
				}
				else {
					if (!m_isPressLeft) {
						m_timerLeft++;
						if (m_timerLeft == 20) {
							m_isPressLeft = true;
							m_timerLeft = 0;
						}
					}
				}
				if (m_isPressLeft) {
					m_se->Stop();
					m_se->Play(false);
					m_optionData->AddColorB(-RGB);
				}
			}
			else {
				m_isTriggerLeft = false;
				m_isPressLeft = false;
				m_timerLeft = 0;
			}
			break;
		case UIData::LightColor::enLightColor_g:	//G
			if (g_pad[0].IsPress(enButtonRight)) {
				if (!m_isTriggerRight) {
					m_optionData->AddColorG(RGB);
					m_isTriggerRight = true;
				}
				else {
					if (!m_isPressRight) {
						m_timerRight++;
						if (m_timerRight == 20) {
							m_isPressRight = true;
							m_timerRight = 0;
						}
					}
				}
				if (m_isPressRight) {
					m_se->Stop();
					m_se->Play(false);
					m_optionData->AddColorG(RGB);
				}
			}
			else {
				m_isTriggerRight = false;
				m_isPressRight = false;
				m_timerRight = 0;
			}
			if (g_pad[0].IsPress(enButtonLeft)) {
				if (!m_isTriggerLeft) {
					m_optionData->AddColorG(-RGB);
					m_isTriggerLeft = true;
				}
				else {
					if (!m_isPressLeft) {
						m_timerLeft++;
						if (m_timerLeft == 20) {
							m_isPressLeft = true;
							m_timerLeft = 0;
						}
					}
				}
				if (m_isPressLeft) {
					m_se->Stop();
					m_se->Play(false);
					m_optionData->AddColorG(-RGB);
				}
			}
			else {
				m_isTriggerLeft = false;
				m_isPressLeft = false;
				m_timerLeft = 0;
			}
			break;
		case UIData::LightColor::enLightColor_r:		//R
			if (g_pad[0].IsPress(enButtonRight)) {
				if (!m_isTriggerRight) {
					m_optionData->AddColorR(RGB);
					m_isTriggerRight = true;
				}
				else {
					if (!m_isPressRight) {
						m_timerRight++;
						if (m_timerRight == 20) {
							m_isPressRight = true;
							m_timerRight = 0;
						}
					}
				}
				if (m_isPressRight) {
					m_se->Stop();
					m_se->Play(false);
					m_optionData->AddColorR(RGB);
				}
			}
			else {
				m_isTriggerRight = false;
				m_isPressRight = false;
				m_timerRight = 0;
			}
			if (g_pad[0].IsPress(enButtonLeft)) {
				if (!m_isTriggerLeft) {
					m_optionData->AddColorR(-RGB);
					m_isTriggerLeft = true;
				}
				else {
					if (!m_isPressLeft) {
						m_timerLeft++;
						if (m_timerLeft == 20) {
							m_isPressLeft = true;
							m_timerLeft = 0;
						}
					}
				}
				if (m_isPressLeft) {
					m_se->Stop();
					m_se->Play(false);
					m_optionData->AddColorR(-RGB);
				}
			}
			else {
				m_isTriggerLeft = false;
				m_isPressLeft = false;
				m_timerLeft = 0;
			}
			break;
		}
	}
}
