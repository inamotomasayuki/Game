#include "stdafx.h"
#include "UISelect.h"
#include "GameData.h"
#include "UIData.h"

UISelect::UISelect()
{
}


UISelect::~UISelect()
{
}

void UISelect::Update()
{
	const auto& m_uiData = &GetUIData();

	switch (m_uiData->GetPageState()) {
	case UIData::Page::enPage_three:
		//ページ操作
		if (g_pad[0].IsTrigger(enButtonB)) {
			m_uiData->PageStateMinus();
			//戻るときは操作したステートをリセットする
			m_uiData->ResetObjState();
			m_uiData->ResetGimmickState();
			m_uiData->ResetEnemyState();
		}
		switch (m_uiData->GetObjMenuState()) {
		case UIData::ObjMenu::enObjMenu_gimmick:
			//ギミックステートを操作
			if (g_pad[0].IsTrigger(enButtonLeft)) {
				m_uiData->GimmickStateMinus();
			}
			if (g_pad[0].IsTrigger(enButtonRight)) {
				m_uiData->GimmickStatePlus();
			}
			break;
		case UIData::ObjMenu::enObjMenu_obj:
			//オブジェクトステートを操作
			if (g_pad[0].IsTrigger(enButtonLeft)) {
				m_uiData->ObjStateMinus();
			}
			if (g_pad[0].IsTrigger(enButtonRight)) {
				m_uiData->ObjStatePlus();
			}
			break;
		case UIData::ObjMenu::enObjMenu_enemy:
			//敵ステートを操作
			if (g_pad[0].IsTrigger(enButtonLeft)) {
				m_uiData->EnemyStateMinus();
			}
			if (g_pad[0].IsTrigger(enButtonRight)) {
				m_uiData->EnemyStatePlus();
			}
			break;
		}
		break;
	case UIData::Page::enPage_two:
		//オブジェクトメニュー操作
		if (g_pad[0].IsTrigger(enButtonDown)) {
			m_uiData->ObjMenuStatePlus();
		}
		if (g_pad[0].IsTrigger(enButtonUp)) {
			m_uiData->ObjMenuStateMinus();
		}
		//ページ操作
		if (g_pad[0].IsTrigger(enButtonA)) {
			m_uiData->PageStatePlus();
		}
		if (g_pad[0].IsTrigger(enButtonB)) {
			m_uiData->PageStateMinus();
			//戻るときは操作したステートをリセット
			m_uiData->ResetObjMenuState();
		}
		break;
	case UIData::Page::enPage_one:
		switch (m_uiData->GetOptionPageState()) {
		case UIData::OptionPage::enOptionPage_one:
			//メニュー操作
			if (g_pad[0].IsTrigger(enButtonDown)) {
				m_uiData->MenuStatePlus();
			}
			if (g_pad[0].IsTrigger(enButtonUp)) {
				m_uiData->MenuStateMinus();
			}
			//UIを閉じるので削除とアップデートを戻す
			if (g_pad[0].IsTrigger(enButtonB)) {
				Delete();
				g_gameData.SetPauseCancel();
			}
			if (m_uiData->GetMenuState() == m_uiData->enMenu_option) {
				//オプション選択中はオプションページ操作
				if (g_pad[0].IsTrigger(enButtonA)) {
					m_uiData->OptionPageStatePlus();
				}
			}
			else {
				//それ以外（リスト選択中）はページ操作
				if (g_pad[0].IsTrigger(enButtonA)) {
					m_uiData->PageStatePlus();
				}
			}
			break;
		case UIData::OptionPage::enOptionPage_two:
			//オプションページ操作
			if (g_pad[0].IsTrigger(enButtonA)) {
				m_uiData->OptionPageStatePlus();
			}
			if (g_pad[0].IsTrigger(enButtonB)) {
				m_uiData->OptionPageStateMinus();
				//戻るときは操作したステートをリセット
				m_uiData->ResetOptionListState();
			}
			//オプションリスト操作
			if (g_pad[0].IsTrigger(enButtonDown)) {
				m_uiData->OptionListStatePlus();
			}
			if (g_pad[0].IsTrigger(enButtonUp)) {
				m_uiData->OptionListStateMinus();
			}
			break;
		case UIData::OptionPage::enOptionPage_three:
			//オプションページ操作
			if (g_pad[0].IsTrigger(enButtonB)) {
				m_uiData->OptionPageStateMinus();
				//戻るときは操作したステートをリセット
				m_uiData->ResetBloomState();
				m_uiData->ResetLightState();
			}
			switch (m_uiData->GetOptionListState()) {
			case UIData::OptionList::enOptionList_bloom:
				//ブルーム操作
				if (g_pad[0].IsTrigger(enButtonDown)) {
					m_uiData->BloomStatePlus();
				}
				if (g_pad[0].IsTrigger(enButtonUp)) {
					m_uiData->BloomStateMinus();
				}
				break;
			case UIData::OptionList::enOptionList_light:
				//ライト操作
				if (g_pad[0].IsTrigger(enButtonDown)) {
					m_uiData->LightStatePlus();
				}
				if (g_pad[0].IsTrigger(enButtonUp)) {
					m_uiData->LightStateMinus();
				}
				if (m_uiData->GetLightState() == m_uiData->enLight_color) {
					if (g_pad[0].IsTrigger(enButtonA)) {
						m_uiData->OptionPageStatePlus();
					}
				}
				break;
			}
			break;
		case UIData::OptionPage::enOptionPage_four:
			switch (m_uiData->GetLightState()) {
			case UIData::Light::enLight_color:
				//ライトカラー操作
				if (g_pad[0].IsTrigger(enButtonUp)) {
					m_uiData->LightColorStateMinus();
				}
				if (g_pad[0].IsTrigger(enButtonDown)) {
					m_uiData->LightColorStatePlus();
				}
				if (g_pad[0].IsTrigger(enButtonB)) {
					m_uiData->OptionPageStateMinus();
					m_uiData->ResetLightColor();
				}
				break;
			}
			break;
		}
		break;
	}
}
