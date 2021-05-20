#include "stdafx.h"
#include "UIManager.h"
#include "UISelect.h"
#include "UISprite.h"
#include "UIText.h"
#include "UIShadowText.h"
#include "../../option/OptionControl.h"
#include "UISound.h"

UIManager::UIManager()
{
	NewUIObject<UISound>();
	NewUIObject<UISelect>();
	NewUIObject<OptionControl>();
	NewUIObject<UISprite>();
	NewUIObject<UIShadowText>();	
	NewUIObject<UIText>();	
}


UIManager::~UIManager()
{
	auto uiData = &GetUIData();
	uiData->Reset();
}

void UIManager::PauseUpdate()
{
	for (auto ui : m_uiList) {
		ui->Update();
		if (ui->GetIsDelete()) {
			g_goMgr.DeleteGameObject(this);
		}
	}
}
void UIManager::Draw2D()
{
	for (auto ui : m_uiList) {
		ui->Draw2D();
	}
}

void UIManager::DrawFont()
{
	for (auto ui : m_uiList) {
		ui->DrawFont();
	}
}