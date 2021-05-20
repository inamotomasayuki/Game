#include "stdafx.h"
#include "UIText.h"
namespace {
	const float MOVE_SPEED = 10.0f;								//移動速度
	const float SELECT_ICON_ROT_SPEED = 0.08f;					//アイコン回転速度
	const float BLOOM_TEXT_ADD_POS_X = 100.0f;					//ブルームテキストX位置加算
	const float LIGHT_TEXT_ADD_POS_X = 200.0f;					//ライトテキストX位置加算
	//拡大率
	const float TEXT_SCALE = 0.4f;								//テキスト拡大率
	const float OPTION_TEXT_SCALE = 0.8f;						//オプションテキスト拡大率
	const float RGB_TEXT_SCALE = 0.7f;							//RGBテキスト拡大率
	const float ICON_SCALE_0 = 0.5f;							//選択アイコン拡大率_0
	const float ICON_SCALE_1 = 0.6f;							//選択アイコン拡大率_1
	//座標
	const CVector2 TITLE_POS = { 500.0f,70.0f };				//タイトル座標
	const CVector2 EXPLANATION_POS = { 320.0f,630.0f };			//タイトル座標
	const CVector2 MENU_POS = { 210.0f,120.0f };				//メニュー座標
	const CVector2 OBJMENU_POS = { 250.0f,190.0f };				//オブジェクトメニュー座標
	const CVector2 OBJ_POS = { 550.0f,300.0f };					//オブジェクト座標
	const CVector2 GIMMICK_POS = { 550.0f,300.0f };				//ギミック座標
	const CVector2 ENEMY_POS = { 550.0f, 300.0f };				//敵座標
	const CVector2 BLOOM_POS = { 500.0f,190.0f };				//ブルーム座標
	const CVector2 LIGHT_POS = { 500.0f,190.0f };				//ライト座標
	const CVector2 LIGHTCOLOR_POS = { 680.0f,200.0f };			//ライトカラー座標
	//並べるための座標加算
	const float ADD_OBJMENU_POS_Y = 120.0f;						//オブジェクトメニュー加算
	const float ADD_POS_X = 105.0f;								//オブジェクト群の加算
	const float ADD_BLOOM_POS_Y = 130.0f;						//ブルーム加算
	const float ADD_LIGHT_POS1_Y = 80.0f;						//ライト加算1
	const float ADD_LIGHT_POS2_Y = 160.0f;						//ライト加算2
	const float ADD_LIGHTCOLOR_POS_Y = 40.0f;					//ライトカラー加算
	const float RGB_POS_X = 30.0f;								//RGBの加算
	//色
	const CVector4 TITLE_COLOR = { 0.0f,0.0f,0.0f,1.0f };		//タイトル色
	const CVector4 SERECT_COLOR = CVector4::White();			//選択中の色
	const CVector4 DEFAULT_COLOR = { 0.3f,0.3f,0.3f,1.0f };		//選択外の色
	const CVector4 SELECT_COLOR2 = { 1.0f,1.0f,0.0f,1.0f };		//選択中の色２
	const CVector4 LIGHT_BLUE = { 0.0f,1.0f,1.0f,1.0f };		//水色
	const CVector4 SELECT_ICON_COLOR = { 1.0f,1.0f,0.0f,1.0f };	//選択アイコンの色
	//RGB
	const CVector4 RED = { 1.0f,0.0f,0.0f,1.0f };			//赤
	const CVector4 GREEN = { 0.0f,1.0f,0.0f,1.0f };			//緑
	const CVector4 BLUE = { 0.0f,0.0f,1.0f,1.0f };			//青
	const CVector4 RGB_COLOR[3] = {
		{1.0f,0.0f,0.0f,1.0f},
		{0.0f,1.0f,0.0f,1.0f},
		{0.0f,0.0f,1.0f,1.0f}
	};
	const CVector2 PIVOT = { 27.8f,21.8f };				//ピボット
	const CVector2 EXPLANATION_SCALE = { 0.5f,0.5f };	//説明スプライトの拡大率
}
UIText::UIText()
{
	m_uiData = &GetUIData();
	//初期化
	Init();
}


UIText::~UIText()
{
}

void UIText::Update()
{
	m_uiData = &GetUIData();
	//移動処理
	Move();
	//色処理
	ColorControl();
	//選択アイコン処理
	SelectControl();
}

void UIText::DrawFont()
{
	//タイトルのテキスト描画
	swprintf_s(m_titleText, L"メニュー画面");
	m_font.DrawScreenPos(
		m_titleText,
		m_titleFontPosition,
		m_titleFontColor
	);
	wchar_t explanationText[256];
	swprintf_s(explanationText, L"( A：進む・決定、B：戻る、上下左右：選択・操作、Rスティックで動くよ)");
	m_font.DrawScreenPos(
		explanationText,
		m_explanationTextPos,
		TITLE_COLOR,
		EXPLANATION_SCALE
	);
	if (m_uiData->GetPageState() >= m_uiData->enPage_two
		|| m_uiData->GetPageState() >= m_uiData->enPage_three
		|| m_uiData->GetOptionPageState() >= m_uiData->enOptionPage_three
		|| m_uiData->GetOptionPageState() >= m_uiData->enOptionPage_four) {
		wchar_t text[256];
		swprintf_s(text, L"＊");
		m_font.DrawScreenPos(
			text,
			m_selectPos,
			m_selectColor,
			m_selectScale,
			PIVOT,
			m_selectRotation
		);
	}
	if (m_uiData->GetPageState() > m_uiData->enPage_one) {
		//オブジェクトメニューのテキスト描画
		for (int i = 0; i < m_uiData->enObjMenu_Num; i++) {
			m_font.DrawScreenPos(
				m_uiData->GetObjMenuTextData(i),
				m_objMenuFontPosition[i],
				m_objMenuFontColor[i],
				m_objMenuFontScale
			);
		}
	}
	if (m_uiData->GetPageState() == m_uiData->enPage_three) {
		switch (m_uiData->GetObjMenuState()) {
		case UIData::ObjMenu::enObjMenu_obj:	//オブジェクトが選択されていたら
			//オブジェクトのテキスト描画
			for (int i = 0; i < m_uiData->enObj_Num; i++) {
				m_font.DrawScreenPos(
					m_uiData->GetObjTextData(i),
					m_objTextPosition[i],
					m_objTextColor[i],
					m_textScale
				);
			}
			break;
		case UIData::ObjMenu::enObjMenu_gimmick:	//ギミックが選択されていたら
			//ギミックのテキスト描画
			for (int i = 0; i < m_uiData->enGimmick_Num; i++) {
				m_font.DrawScreenPos(
					m_uiData->GetGimmickTextData(i),
					m_gimmickTextPosition[i],
					m_gimmickTextColor[i],
					m_textScale
				);
			}
			break;
		case UIData::ObjMenu::enObjMenu_enemy:		//敵が選択されていたら
			//敵のテキスト描画
			for (int i = 0; i < m_uiData->enEnemy_Num; i++) {
				m_font.DrawScreenPos(
					m_uiData->GetEnemyTextData(i),
					m_enemyTextPosition[i],
					m_enemyTextColor[i],
					m_textScale
				);
			}
			break;
		}
	}
	if (m_uiData->GetOptionPageState() >= m_uiData->enOptionPage_three) {
		switch (m_uiData->GetOptionListState()) {
		case UIData::OptionList::enOptionList_bloom:	//ブルームが選択されていたら
			//ブルームのテキスト描画
			for (int i = 0; i < m_uiData->enBloom_Num; i++) {
				m_font.DrawScreenPos(
					m_uiData->GetBloomTextData(i),
					m_bloomTextPosition[i],
					m_bloomTextColor[i],
					m_optionTextScale
				);
			}
			m_optionData = &GetOptionData();
			wchar_t text[256];
			swprintf_s(text, L"%01d", static_cast<int>(m_optionData->GetLumCount()));
			m_pos = m_bloomTextPosition[m_uiData->enBloom_luminance];
			m_pos.x += BLOOM_TEXT_ADD_POS_X;
			m_font.DrawScreenPos(
				text,
				m_pos,
				LIGHT_BLUE,
				m_scale
			);
			swprintf_s(text, L"%01d", static_cast<int>(m_optionData->GetPowCount()));
			m_pos = m_bloomTextPosition[m_uiData->enBloom_pow];
			m_pos.x += BLOOM_TEXT_ADD_POS_X;
			m_font.DrawScreenPos(
				text,
				m_pos,
				LIGHT_BLUE,
				m_scale
			);
			break;
		case UIData::OptionList::enOptionList_light:	//ライトが選択されていたら
			//ライトのテキスト描画
			for (int i = 0; i < m_uiData->enLight_Num; i++) {
				m_font.DrawScreenPos(
					m_uiData->GetLightTextData(i),
					m_lightTextPosition[i],
					m_lightTextColor[i],
					m_optionTextScale
				);
			}
			//ライトカラーのテキスト描画
			for (int i = 0; i < m_uiData->enLightColor_Num; i++) {
				m_font.DrawScreenPos(
					m_uiData->GetLightColorTextData(i),
					m_lightColorTextPosition[i],
					m_lightColorTextColor[i],
					m_rgbScale
				);
			}
			m_optionData = &GetOptionData();
			swprintf_s(text, L"%01d", static_cast<int>(m_optionData->GetCountColorR()));
			m_pos = m_lightColorTextPosition[m_uiData->enLightColor_r];
			m_pos.x += RGB_POS_X;
			m_font.DrawScreenPos(
				text,
				m_pos,
				RED,
				m_scale
			);
			swprintf_s(text, L"%01d", static_cast<int>(m_optionData->GetCountColorG()));
			m_pos = m_lightColorTextPosition[m_uiData->enLightColor_g];
			m_pos.x += RGB_POS_X;
			m_font.DrawScreenPos(
				text,
				m_pos,
				GREEN,
				m_scale
			);
			swprintf_s(text, L"%01d", static_cast<int>(m_optionData->GetCountColorB()));
			m_pos = m_lightColorTextPosition[m_uiData->enLightColor_b];
			m_pos.x += RGB_POS_X;
			m_font.DrawScreenPos(
				text,
				m_pos,
				BLUE,
				m_scale
			);
			swprintf_s(text, L"%01d", static_cast<int>(m_optionData->GetBrightnessCount()));
			m_pos = m_lightTextPosition[m_uiData->enLight_brightness];
			m_pos.x += LIGHT_TEXT_ADD_POS_X;
			m_font.DrawScreenPos(
				text,
				m_pos,
				LIGHT_BLUE,
				m_scale
			);
			swprintf_s(text, L"%01d", static_cast<int>(m_optionData->GetSkyBrightnessCount()));
			m_pos = m_lightTextPosition[m_uiData->enLight_skyBrightness];
			m_pos.x += LIGHT_TEXT_ADD_POS_X;
			m_font.DrawScreenPos(
				text,
				m_pos,
				LIGHT_BLUE,
				m_scale
			);
			break;
		}
	}

}

void UIText::Init()
{
	//位置と色と拡大率の初期化
	auto addPos = CVector2::Zero();
	//タイトルの初期化
	m_titleFontPosition = TITLE_POS;
	m_titleFontColor = TITLE_COLOR;
	m_explanationTextPos = EXPLANATION_POS;
	//オブジェクトメニューの初期化
	for (int i = 0; i < m_uiData->enObjMenu_Num; i++) {
		m_objMenuFontColor[i] = DEFAULT_COLOR;
		m_objMenuFontPosition[i] = OBJMENU_POS + addPos;
		addPos.y += ADD_OBJMENU_POS_Y;
	}
	m_objMenuFontScale = CVector2::One() *= 0.8f;
	addPos = CVector2::Zero();
	//オブジェクトの初期化
	for (int i = 0; i < m_uiData->enObj_Num; i++) {
		m_objTextColor[i] = DEFAULT_COLOR;
		m_objTextPosition[i] = OBJ_POS + addPos;
		addPos.x += ADD_POS_X;
	}
	addPos = CVector2::Zero();
	//ギミックの初期化
	for (int i = 0; i < m_uiData->enGimmick_Num; i++) {
		m_gimmickTextColor[i] = DEFAULT_COLOR;
		m_gimmickTextPosition[i] = GIMMICK_POS + addPos;
		addPos.x += ADD_POS_X;
	}
	addPos = CVector2::Zero();
	//敵の初期化
	for (int i = 0; i < m_uiData->enEnemy_Num; i++) {
		m_enemyTextColor[i] = DEFAULT_COLOR;
		m_enemyTextPosition[i] = ENEMY_POS + addPos;
		addPos.x += ADD_POS_X;
	}
	addPos = CVector2::Zero();
	//ブルームの初期化
	for (int i = 0; i < m_uiData->enBloom_Num; i++) {
		m_bloomTextColor[i] = DEFAULT_COLOR;
		m_bloomTextPosition[i] = BLOOM_POS + addPos;
		addPos.y += ADD_BLOOM_POS_Y;
	}
	addPos = CVector2::Zero();
	//ライトの初期化
	for (int i = 0; i < m_uiData->enLight_Num; i++) {
		m_lightTextColor[i] = DEFAULT_COLOR;
		m_lightTextPosition[i] = LIGHT_POS + addPos;
		if (i != 0) {
			addPos.y += ADD_LIGHT_POS1_Y;
		}
		else {
			addPos.y += ADD_LIGHT_POS2_Y;
		}
	}
	addPos = CVector2::Zero();
	//ライトカラーの初期化
	for (int i = 0; i < m_uiData->enLightColor_Num; i++) {
		m_lightColorTextColor[i] = DEFAULT_COLOR;
		m_lightColorTextPosition[i] = LIGHTCOLOR_POS + addPos;
		addPos.y += ADD_LIGHTCOLOR_POS_Y;
	}
	//アイコンの色
	m_selectColor = SELECT_ICON_COLOR;
	//テキスト拡大率
	m_textScale *= TEXT_SCALE;
	m_optionTextScale *= OPTION_TEXT_SCALE;
	m_rgbScale *= RGB_TEXT_SCALE;
}
void UIText::Move()
{
	//移動処理
	//タイトル
	MovePosUpdate(
		&m_titleFontPosition
	);
	MovePosUpdate(
		&m_explanationTextPos
	);
	//オブジェクトメニュー
	MovePosUpdate(
		&m_objMenuFontPosition[0],
		m_uiData->enObjMenu_Num
	);
	//オブジェクト
	MovePosUpdate(
		&m_objTextPosition[0],
		m_uiData->enObj_Num
	);
	//ギミック
	MovePosUpdate(
		&m_gimmickTextPosition[0],
		m_uiData->enGimmick_Num
	);
	//敵
	MovePosUpdate(
		&m_enemyTextPosition[0],
		m_uiData->enEnemy_Num
	);
	//ブルーム
	MovePosUpdate(
		&m_bloomTextPosition[0],
		m_uiData->enBloom_Num
	);
	//ライト
	MovePosUpdate(
		&m_lightTextPosition[0],
		m_uiData->enLight_Num
	);
	//ライトカラー
	MovePosUpdate(
		&m_lightColorTextPosition[0],
		m_uiData->enLightColor_Num
	);
}
void UIText::MovePosUpdate(CVector2 movePos[], int en_Num)
{
	m_moveSpeed.x = g_pad->GetRStickXF() * MOVE_SPEED;
	m_moveSpeed.y = g_pad->GetRStickYF() * MOVE_SPEED;
	for (int i = 0; i < en_Num; i++) {
		movePos[i].x += m_moveSpeed.x;
		movePos[i].y -= m_moveSpeed.y;
	}
}
void UIText::SetSelectPos(CVector2 setPos[], int CurrentNum, int arrayNum, float posX, float posY)
{
	for (int i = 0; i < arrayNum; i++) {
		if (CurrentNum == i) {
			m_selectPos = setPos[i];
			m_selectPos.x += posX;
			m_selectPos.y += posY;
		}
	}
}
void UIText::SelectControl()
{
	//位置
	if (m_uiData->GetPageState() >= m_uiData->enPage_two) {
		SetSelectPos(m_objMenuFontPosition, m_uiData->GetObjMenuState(), m_uiData->enObjMenu_Num, 0.0f, 15.0f);
		m_selectScale = CVector2::One();
	}
	if (m_uiData->GetPageState() >= m_uiData->enPage_three) {
		if (m_uiData->GetObjMenuState() >= m_uiData->enObjMenu_obj) {
			SetSelectPos(m_objTextPosition, m_uiData->GetObjState(), m_uiData->enObj_Num, -10.0f, 10.0f);
		}
		if (m_uiData->GetObjMenuState() >= m_uiData->enObjMenu_gimmick) {
			SetSelectPos(m_gimmickTextPosition, m_uiData->GetGimmickState(), m_uiData->enGimmick_Num, -10.0f, 10.0f);
		}
		if (m_uiData->GetObjMenuState() >= m_uiData->enObjMenu_enemy) {
			SetSelectPos(m_enemyTextPosition, m_uiData->GetEnemyState(), m_uiData->enEnemy_Num, -10.0f, 10.0f);
		}
		m_selectScale = CVector2::One() * ICON_SCALE_0;
	}
	if (m_uiData->GetOptionPageState() >= m_uiData->enOptionPage_three) {
		if (m_uiData->GetOptionListState() == m_uiData->enOptionList_bloom) {
			SetSelectPos(m_bloomTextPosition, m_uiData->GetBloomState(), m_uiData->enBloom_Num, -10.0f, 18.0f);
		}
		if (m_uiData->GetOptionListState() == m_uiData->enOptionList_light) {
			SetSelectPos(m_lightTextPosition, m_uiData->GetLightState(), m_uiData->enLight_Num, -10.0f, 18.0f);
		}
		m_selectScale = CVector2::One();
	}
	if (m_uiData->GetOptionPageState() >= m_uiData->enOptionPage_four) {
		SetSelectPos(m_lightColorTextPosition, m_uiData->GetLightColorState(), m_uiData->enLightColor_Num, -10.0f, 15.0f);
		m_selectScale = CVector2::One() * ICON_SCALE_1;
	}
	//回転
	m_selectRotation += SELECT_ICON_ROT_SPEED;
	if (m_selectRotation >= 360) {
		m_selectRotation = 0.0f;
	}
}
void UIText::ColorUpdate(
	CVector4 color[],
	int array_Num,
	int Current_Num,
	const CVector4& setColor0,
	const CVector4& setColor1
)
{
	for (int i = 0; i < array_Num; i++) {
		if (Current_Num == i) {
			color[i] = setColor0;
		}
		if (Current_Num != i) {
			color[i] = setColor1;
		}
	}
}
void UIText::ColorUpdate(
	CVector4 color[],
	int array_Num,
	int Current_Num,
	const CVector4 setColor0[],
	const CVector4& setColor1
)
{
	for (int i = 0; i < array_Num; i++) {
		if (Current_Num == i) {
			color[i] = setColor0[i];
		}
		if (Current_Num != i) {
			color[i] = setColor1;
		}
	}
}
void UIText::DefaultColor(
	CVector4 color[],
	const CVector4& defaultColor,
	int array_Num
)
{
	for (int i = 0; i < array_Num; i++) {
		color[i] = defaultColor;
	}
}

void UIText::ColorControl()
{
	//テキストの色
	if (m_uiData->GetPageState() >= m_uiData->enPage_two) {
		//オブジェクトメニュー
		ColorUpdate(
			m_objMenuFontColor,
			m_uiData->enObjMenu_Num,
			m_uiData->GetObjMenuState(),
			SERECT_COLOR,
			DEFAULT_COLOR
		);
	}
	else {
		//デフォ
		DefaultColor(
			m_objMenuFontColor,
			DEFAULT_COLOR,
			m_uiData->enObjMenu_Num
		);
	}
	if (m_uiData->GetPageState() >= m_uiData->enPage_three) {
		if (m_uiData->GetObjMenuState() == m_uiData->enObjMenu_obj) {
			//オブジェクト
			ColorUpdate(
				m_objTextColor,
				m_uiData->enObj_Num,
				m_uiData->GetObjState(),
				SELECT_COLOR2,
				DEFAULT_COLOR
			);
		}
		else if (m_uiData->GetObjMenuState() == m_uiData->enObjMenu_gimmick) {
			//ギミック
			ColorUpdate(
				m_gimmickTextColor,
				m_uiData->enGimmick_Num,
				m_uiData->GetGimmickState(),
				SELECT_COLOR2,
				DEFAULT_COLOR
			);
		}
		else if (m_uiData->GetObjMenuState() == m_uiData->enObjMenu_enemy) {
			//敵
			ColorUpdate(
				m_enemyTextColor,
				m_uiData->enEnemy_Num,
				m_uiData->GetEnemyState(),
				SELECT_COLOR2,
				DEFAULT_COLOR
			);
		}
	}
	else {
		//デフォ
		DefaultColor(
			m_objTextColor,
			DEFAULT_COLOR,
			m_uiData->enObj_Num
		);
		DefaultColor(
			m_gimmickTextColor,
			DEFAULT_COLOR,
			m_uiData->enGimmick_Num
		);
		DefaultColor(
			m_enemyTextColor,
			DEFAULT_COLOR,
			m_uiData->enEnemy_Num
		);
	}
	if (m_uiData->GetOptionPageState() == m_uiData->enOptionPage_three) {
		if (m_uiData->GetOptionListState() == m_uiData->enOptionList_bloom) {
			//ブルーム
			ColorUpdate(
				m_bloomTextColor,
				m_uiData->enBloom_Num,
				m_uiData->GetBloomState(),
				SERECT_COLOR,
				DEFAULT_COLOR
			);
		}
		else {
			//デフォ
			DefaultColor(
				m_bloomTextColor,
				DEFAULT_COLOR,
				m_uiData->enBloom_Num
			);
		}
		if (m_uiData->GetOptionListState() == m_uiData->enOptionList_light) {
			//ライト
			ColorUpdate(
				m_lightTextColor,
				m_uiData->enLight_Num,
				m_uiData->GetLightState(),
				SERECT_COLOR,
				DEFAULT_COLOR
			);
		}
		else {
			//デフォ
			DefaultColor(
				m_lightTextColor,
				DEFAULT_COLOR,
				m_uiData->enLight_Num
			);
		}
		for (int i = 0; i < m_uiData->enLightColor_Num; i++) {
			m_lightColorTextColor[i] = RGB_COLOR[i];
		}
	}
}