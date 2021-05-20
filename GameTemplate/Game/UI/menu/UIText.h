#pragma once
#include "IUIObject.h"
#include "../../graphics/2D/Font.h"
#include "UIData.h"
class UIText : public IUIObject
{
public:
	UIText();
	~UIText();
	/*!
	*@brief 更新
	*/
	void Update() override;
	/*!
	*@brief フォント描画
	*/
	void DrawFont() override;
protected:
	/*!
	*@brief	テキストの色の更新
	*@param[in]	color			変更する色 [ 配列 ]
	*@param[in]	array_Num		配列の数　デフォルト１
	*@param[in] Current_Num		変更したい要素
	*@param[in] setColor0		指定した変更したい要素に対する色
	*@param[in] setColor1		それ以外の要素の色
	*/
	void ColorUpdate(
		CVector4 color[],
		int array_Num,
		int Current_Num,
		const CVector4& setColor0,
		const CVector4& setColor1
	);
	/*!
	*@brief	テキストの色の更新
	*@param[in]	color			変更する色 [ 配列 ]
	*@param[in]	array_Num		配列の数　デフォルト１	
	*@param[in] Current_Num		変更したい要素
	*@param[in] setColor0		指定した変更したい要素に対する色
	*@param[in] setColor1		それ以外の要素の色
	*/
	void ColorUpdate(
		CVector4 color[],
		int array_Num,
		int Current_Num,
		const CVector4 setColor0[],
		const CVector4& setColor1
	);

	/*!
	*@brief　デフォルトカラーに設定
	*@param[in] color　　　　　変更する色　[ 配列 ]
	*@param[in] defaultcolor　　デフォルトカラー
	*@param[in]	array_Num　　配列要素数　デフォルト１
	*/
	void DefaultColor(
		CVector4 color[],
		const CVector4& defaultColor,
		int array_Num = 1
	);
	/*!
	*@brief　移動処理
	*@param[in] movePos　位置　[ 配列 ]
	*@param[in] en_Num　配列要素数
	*/
	void MovePosUpdate(CVector2 movePos[], int en_Num = 1);
	/*!
	*@brief　選択アイコンの位置設定
	*@param[in] setPos　選択位置　[ 配列 ]
	*@param[in] CurrentNum  選択中の要素
	*@param[in] arrayNum　配列要素数
	*@param[in] posX 設定するX座標
	*@param[in] posY 設定するY座標
	*/
	void SetSelectPos(CVector2 setPos[], int CurrentNum = 0, int arrayNum = 1, float posX = 0.0f, float posY = 0.0f);
private:
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 移動操作
	/// </summary>
	void Move();
	/// <summary>
	/// 色操作
	/// </summary>
	void ColorControl();
	/*!
	*@brief 選択アイコン操作
	*/
	void SelectControl();
protected:
	UIData* m_uiData = nullptr;					//UIデータ
	Font m_font;								//フォント
	wchar_t m_titleText[256];									//タイトルテキスト
	CVector2 m_titleFontPosition = CVector2::Zero();			//タイトルの位置
	CVector4 m_titleFontColor = CVector4::White();				//タイトルの色

	CVector2 m_explanationTextPos = CVector2::Zero();

	CVector2 m_objTextPosition[UIData::Obj::enObj_Num];			//オブジェクトテキストの位置
	CVector4 m_objTextColor[UIData::Obj::enObj_Num];			//オブジェクトテキストの色

	CVector2 m_gimmickTextPosition[UIData::Gimmick::enGimmick_Num];		//ギミックテキストの位置
	CVector4 m_gimmickTextColor[UIData::Gimmick::enGimmick_Num];		//ギミックテキストの色

	CVector2 m_enemyTextPosition[UIData::Enemy::enEnemy_Num];			//敵テキストの位置
	CVector4 m_enemyTextColor[UIData::Enemy::enEnemy_Num];				//敵テキストの色

	CVector2 m_bloomTextPosition[UIData::Bloom::enBloom_Num];			//ブルームテキストの位置
	CVector4 m_bloomTextColor[UIData::Bloom::enBloom_Num];				//ブルームテキストの色

	CVector2 m_lightTextPosition[UIData::Light::enLight_Num];			//ライトテキストの位置
	CVector4 m_lightTextColor[UIData::Light::enLight_Num];				//ライトテキストの色

	CVector2 m_lightColorTextPosition[UIData::LightColor::enLightColor_Num];			//ライトカラーテキストの位置
	CVector4 m_lightColorTextColor[UIData::LightColor::enLightColor_Num];				//ライトカラーテキストの色

	CVector2 m_textScale = CVector2::One();								//テキストの拡大率
	CVector2 m_optionTextScale = CVector2::One();						//オプションテキストの拡大率
	CVector2 m_rgbScale = CVector2::One();								//ＲＧＢのテキスト拡大率

	CVector2 m_objMenuFontPosition[UIData::ObjMenu::enObjMenu_Num];		//オブジェクトメニューテキストの位置
	CVector4 m_objMenuFontColor[UIData::ObjMenu::enObjMenu_Num];		//オブジェクトメニューテキストの色
	CVector2 m_objMenuFontScale = CVector2::One();						//オブジェクトメニューの拡大率

	CVector2 m_moveSpeed;												//移動速度
	CVector2 m_pos;														//位置
	CVector2 m_scale = CVector2::One() * 0.8f;							//拡大率
	OptionData* m_optionData = nullptr;									//オプションデータ

	CVector2 m_selectPos = CVector2::Zero();						//選択アイコンの位置
	CVector4 m_selectColor = CVector4::White();						//選択アイコンの色
	CVector2 m_selectScale = CVector2::One();						//選択アイコンの拡大率
	float m_selectRotation = 0.0f;									//選択アイコン回転
};
