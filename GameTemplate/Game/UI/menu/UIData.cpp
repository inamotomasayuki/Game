#include "stdafx.h"
#include "UIData.h"

UIData::UIData()
{
	//テキスト初期化
	TextDataInit();
	//スプライトのファイルパス初期化
	SpriteFilePathInit();
}

void UIData::TextDataInit()
{
	//メニューテキストデータ
	swprintf_s(m_menutextData[enMenu_list], L"・リスト");
	swprintf_s(m_menutextData[enMenu_option], L"＜オプション＞");
	//オブジェクトメニューテキストデータ
	swprintf_s(m_objMenutextData[enObjMenu_gimmick], L"・ギミック");
	swprintf_s(m_objMenutextData[enObjMenu_obj], L"・オブジェクト");
	swprintf_s(m_objMenutextData[enObjMenu_enemy], L"・敵キャラ");
	//オブジェクトテキストデータ
	swprintf_s(m_objTextData[enObj_coin], L"コイン");
	swprintf_s(m_objTextData[enObj_mikan], L"みかん");
	swprintf_s(m_objTextData[enObj_star], L"スター");
	//ギミックテキストデータ
	swprintf_s(m_gimmickTextData[enGiimick_MoveFloor], L"動く床");
	swprintf_s(m_gimmickTextData[enGimmick_button], L"ボタン");
	swprintf_s(m_gimmickTextData[enGimmick_box], L"ボックス");
	swprintf_s(m_gimmickTextData[enGimmick_jumpFloor], L"ジャンプ床");
	swprintf_s(m_gimmickTextData[enGimmick_warp], L"ワープ床");
	//敵テキストデータ
	swprintf_s(m_enemyTextData[enEnemy_kame], L"カメ");
	swprintf_s(m_enemyTextData[enEnemy_kuribo], L"くりぼう");
	swprintf_s(m_enemyTextData[enEmemy_wingKuribo], L"羽根\nくりぼう");
	//ライトテキストデータ
	swprintf_s(m_optionListTextData[enOptionList_light], L"・ライト");
	swprintf_s(m_optionListTextData[enOptionList_bloom], L"・ブルーム");
	//ブルームテキストデータ
	swprintf_s(m_bloomTextData[enBloom_luminance], L"輝度");
	swprintf_s(m_bloomTextData[enBloom_pow], L"強さ");
	swprintf_s(m_bloomTextData[enBloom_init], L"初期化");
	//ライトテキストデータ
	swprintf_s(m_lightTextData[enLight_color], L"色設定");
	swprintf_s(m_lightTextData[enLight_brightness], L"明るさ");
	swprintf_s(m_lightTextData[enLight_skyBrightness], L"空の明るさ");
	swprintf_s(m_lightTextData[enLight_init], L"初期化");
	//ライトカラーテキストデータ
	swprintf_s(m_lightColorTextData[enLightColor_r], L"R");
	swprintf_s(m_lightColorTextData[enLightColor_g], L"G");
	swprintf_s(m_lightColorTextData[enLightColor_b], L"B");
}

void UIData::SpriteFilePathInit()
{
	//オブジェクトスプライトファイルパス
	swprintf_s(m_objSpriteFilePath[enObj_coin], L"Assets/sprite/uiCoin.dds");
	swprintf_s(m_objSpriteFilePath[enObj_mikan], L"Assets/sprite/mikan.dds");
	swprintf_s(m_objSpriteFilePath[enObj_star], L"Assets/sprite/star.dds");
	//ギミックスプライトファイルパス
	swprintf_s(m_gimmickSpriteFilePath[enGiimick_MoveFloor], L"Assets/sprite/moveFloor.dds");
	swprintf_s(m_gimmickSpriteFilePath[enGimmick_button], L"Assets/sprite/button.dds");
	swprintf_s(m_gimmickSpriteFilePath[enGimmick_box], L"Assets/sprite/box.dds");
	swprintf_s(m_gimmickSpriteFilePath[enGimmick_jumpFloor], L"Assets/sprite/jumpFloor.dds");
	swprintf_s(m_gimmickSpriteFilePath[enGimmick_warp], L"Assets/sprite/warp.dds");
	//敵スプライトファイルパス
	swprintf_s(m_enemySpriteFilePath[enEnemy_kame], L"Assets/sprite/kame.dds");
	swprintf_s(m_enemySpriteFilePath[enEnemy_kuribo], L"Assets/sprite/kuribo.dds");
	swprintf_s(m_enemySpriteFilePath[enEmemy_wingKuribo], L"Assets/sprite/wingKuribo.dds");
}
void UIData::Reset()
{
	//ステートをリセット
	m_pageState = static_cast<Page>(0);
	m_optionPageState = static_cast<OptionPage>(0);
	m_menuState = static_cast<Menu>(0);
	m_objMenuState = static_cast<ObjMenu>(0);
	m_objState = static_cast<Obj>(0);
	m_gimmickState = static_cast<Gimmick>(0);
	m_enemyState = static_cast<Enemy>(0);
	m_optionListState = static_cast<OptionList>(0);
	m_bloomState = static_cast<Bloom>(0);
	m_lightState = static_cast<Light>(0);
	m_lightColorState = static_cast<LightColor>(0);
}