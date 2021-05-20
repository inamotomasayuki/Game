#pragma once
class UIData final
{
public:
	UIData();
	/// <summary>
	/// テキストデータ設定
	/// </summary>
	void TextDataInit();
	/// <summary>
	/// スプライトファイルパス設定
	/// </summary>
	void SpriteFilePathInit();
	/// <summary>
	/// ステートリセット
	/// </summary>
	void Reset();
	static UIData& GetInstance()
	{
		static UIData instance;
		return instance;
	}
	//リストページ
	enum Page {
		enPage_one,			//ページ１
		enPage_two,			//ページ２
		enPage_three,		//ページ３
		enPage_Num			//数
	};
	//オプションページ
	enum OptionPage {
		enOptionPage_one,		//オプションページ１
		enOptionPage_two,		//オプションページ２
		enOptionPage_three,		//オプションページ３
		enOptionPage_four,		//オプションページ４
		enOptionPage_Num		//数
	};
	//メニュー
	enum Menu {
		enMenu_list,			//リスト
		enMenu_option,			//オプション
		enMenu_Num				//数
	};
	//リストメニュー
	enum ObjMenu {
		enObjMenu_obj,			//オブジェクト
		enObjMenu_gimmick,		//ギミック
		enObjMenu_enemy,		//敵
		enObjMenu_Num			//数
	};
	//オブジェクト
	enum Obj {
		enObj_mikan,			//みかん
		enObj_coin,				//コイン
		enObj_star,				//スター
		enObj_Num				//数
	};
	//ギミック
	enum Gimmick {
		enGimmick_warp,			//ワープ
		enGimmick_box,			//ボックス
		enGimmick_button,		//ボタン
		enGiimick_MoveFloor,	//動く床
		enGimmick_jumpFloor,	//ジャンプ床
		enGimmick_Num			//数
	};
	//敵
	enum Enemy {
		enEnemy_kuribo,			//くりぼう
		enEmemy_wingKuribo,		//羽根くりぼう
		enEnemy_kame,			//カメ
		enEnemy_Num				//数
	};
	//オプションリスト
	enum OptionList
	{
		enOptionList_light,		//ライト
		enOptionList_bloom,		//ブルーム
		enOptionList_Num		//数
	};
	//ブルーム
	enum Bloom
	{
		enBloom_luminance,		//輝度
		enBloom_pow,			//強さ
		enBloom_init,			//初期化
		enBloom_Num				//数
	};
	//ライト
	enum Light
	{
		enLight_color,			//色
		enLight_brightness,		//明るさ
		enLight_skyBrightness,	//空の明るさ
		enLight_init,			//初期化
		enLight_Num				//数
	};
	//ライトカラー
	enum LightColor
	{
		enLightColor_r,		//R
		enLightColor_g,		//G
		enLightColor_b,		//B
		enLightColor_Num		//数
	};
private:
	//リストのステート
	Page m_pageState = static_cast<Page>(0);						//ページステート
	OptionPage m_optionPageState = static_cast<OptionPage>(0);	//オプションページステート
	Menu m_menuState = static_cast<Menu>(0);						//メニューステート
	ObjMenu m_objMenuState = static_cast<ObjMenu>(0);			//リストメニューステート
	Obj m_objState = static_cast<Obj>(0);						//オブジェクトステート
	Gimmick m_gimmickState = static_cast<Gimmick>(0);			//ギミックステート
	Enemy m_enemyState = static_cast<Enemy>(0);					//敵ステート
	OptionList m_optionListState = static_cast<OptionList>(0);	//オプションリストステート
	Bloom m_bloomState = static_cast<Bloom>(0);					//ブルームステート
	Light m_lightState = static_cast<Light>(0);					//ライトステート
	LightColor m_lightColorState = static_cast<LightColor>(0);		//ライトカラーステート
	//テキストデータ
	wchar_t m_menutextData[enMenu_Num][256];				//メニューテキスト
	wchar_t m_objMenutextData[enObjMenu_Num][256];			//リストメニューテキスト
	wchar_t m_objTextData[enObj_Num][256];					//オブジェクトテキスト
	wchar_t m_gimmickTextData[enGimmick_Num][256];			//ギミックテキスト
	wchar_t m_enemyTextData[enEnemy_Num][256];				//敵テキスト
	wchar_t m_optionListTextData[enOptionList_Num][256];	//オプションリストテキスト
	wchar_t m_bloomTextData[enBloom_Num][256];				//ブルームテキスト
	wchar_t m_lightTextData[enLight_Num][256];				//ライトテキスト
	wchar_t m_lightColorTextData[enLightColor_Num][256];	//ライトカラーテキストデータ
	//ファイルパス
	wchar_t m_objSpriteFilePath[enObj_Num][256];			//オブジェクトスプライトファイルパス
	wchar_t m_gimmickSpriteFilePath[enGimmick_Num][256];	//ギミックスプライトファイルパス
	wchar_t m_enemySpriteFilePath[enEnemy_Num][256];		//敵スプライトファイルパス
public:
	//テキストデータの取得群
	/// <summary>
	/// メニューテキストデータの取得
	/// </summary>
	/// <param name="i">何番目のテキストか指定</param>
	/// <returns>指定した番目のテキスト</returns>
	wchar_t* GetMenuTextData(int i = 0)
	{
		return &m_menutextData[i - 1][256];
	}
	/// <summary>
	/// オブジェクトメニューテキストデータの取得
	/// </summary>
	/// <param name="i">何番目のテキストか指定</param>
	/// <returns>指定した番目のテキスト</returns>
	wchar_t* GetObjMenuTextData(int i = 0)
	{
		return &m_objMenutextData[i - 1][256];
	}
	/// <summary>
	/// オブジェクトテキストデータの取得
	/// </summary>
	/// <param name="i">何番目のテキストか指定</param>
	/// <returns>指定した番目のテキスト</returns>
	wchar_t* GetObjTextData(int i = 0)
	{
		return &m_objTextData[i - 1][256];
	}
	/// <summary>
	/// ギミックテキストデータの取得
	/// </summary>
	/// <param name="i">何番目のテキストか指定</param>
	/// <returns>指定した番目のテキスト</returns>
	wchar_t* GetGimmickTextData(int i = 0)
	{
		return &m_gimmickTextData[i - 1][256];
	}
	/// <summary>
	/// 敵テキストデータの取得
	/// </summary>
	/// <param name="i">何番目のテキストか指定</param>
	/// <returns>指定した番目のテキスト</returns>
	wchar_t* GetEnemyTextData(int i = 0)
	{
		return &m_enemyTextData[i - 1][256];
	}
	/// <summary>
	/// オプションリストテキストデータの取得
	/// </summary>
	/// <param name="i">何番目のテキストか指定</param>
	/// <returns>指定した番目のテキスト</returns>
	wchar_t* GetOptionListTextData(int i = 0)
	{
		return &m_optionListTextData[i - 1][256];
	}
	/// <summary>
	/// ブルームテキストデータの取得
	/// </summary>
	/// <param name="i">何番目のテキストか指定</param>
	/// <returns>指定した番目のテキスト</returns>
	wchar_t* GetBloomTextData(int i = 0)
	{
		return &m_bloomTextData[i - 1][256];
	}
	/// <summary>
	/// ライトテキストデータの取得
	/// </summary>
	/// <param name="i">何番目のテキストか指定</param>
	/// <returns>指定した番目のテキスト</returns>
	wchar_t* GetLightTextData(int i = 0)
	{
		return &m_lightTextData[i - 1][256];
	}
	/// <summary>
	/// ライトカラーテキストデータの取得
	/// </summary>
	/// <param name="i">何番目のテキストか指定</param>
	/// <returns>指定した番目のテキスト</returns>
	wchar_t* GetLightColorTextData(int i = 0)
	{
		return &m_lightColorTextData[i - 1][256];
	}
public:
	//ファイルパス取得群
	/// <summary>
	/// オブジェクトスプライトファイルパスの取得
	/// </summary>
	/// <param name="i">何番目のファイルパスか指定</param>
	/// <returns>指定した番目のファイルパス</returns>
	wchar_t* GetObjSpriteFilePath(int i = 0)
	{
		return &m_objSpriteFilePath[i - 1][256];
	}
	/// <summary>
	/// ギミックスプライトファイルパスの取得
	/// </summary>
	/// <param name="i">何番目のファイルパスか指定</param>
	/// <returns>指定した番目のファイルパス</returns>
	wchar_t* GetGimmickSpriteFilePath(int i = 0)
	{
		return &m_gimmickSpriteFilePath[i - 1][256];
	}
	/// <summary>
	/// 敵スプライトファイルパスの取得
	/// </summary>
	/// <param name="i">何番目のファイルパスか指定</param>
	/// <returns>指定した番目のファイルパス</returns>
	wchar_t* GetEnemySpriteFilePath(int i = 0)
	{
		return &m_enemySpriteFilePath[i - 1][256];
	}
public:
	//ステートリセット群
	/// <summary>
	/// オブジェクトメニューステートのリセット
	/// </summary>
	void ResetObjMenuState()
	{
		m_objMenuState = static_cast<ObjMenu>(0);
	}
	/// <summary>
	/// オブジェクトステートのリセット
	/// </summary>
	void ResetObjState()
	{
		m_objState = static_cast<Obj>(0);
	}
	/// <summary>
	/// ギミックステートのリセット
	/// </summary>
	void ResetGimmickState()
	{
		m_gimmickState = static_cast<Gimmick>(0);
	}
	/// <summary>
	/// 敵ステートのリセット
	/// </summary>
	void ResetEnemyState()
	{
		m_enemyState = static_cast<Enemy>(0);
	}
	/// <summary>
	/// オプションリストステートのリセット
	/// </summary>
	void ResetOptionListState()
	{
		m_optionListState = static_cast<OptionList>(0);
	}
	/// <summary>
	/// ブルームステートのリセット
	/// </summary>
	void ResetBloomState()
	{
		m_bloomState = static_cast<Bloom>(0);
	}
	/// <summary>
	/// ライトステートのリセット
	/// </summary>
	void ResetLightState()
	{
		m_lightState = static_cast<Light>(0);
	}
	/// <summary>
	/// ライトカラーステートのリセット
	/// </summary>
	void ResetLightColor()
	{
		m_lightColorState = static_cast<LightColor>(0);
	}
public:
	//ステートの加算減算群
	/// <summary>
	/// ページステートの加算
	/// </summary>
	void PageStatePlus()
	{
		m_pageState = static_cast<Page>(m_pageState + 1);
		if (m_pageState >= enPage_Num) {
			m_pageState = static_cast<Page>(enPage_Num - 1);
		}
	}
	/// <summary>
	/// ページステートの減算
	/// </summary>
	void PageStateMinus()
	{
		m_pageState = static_cast<Page>(m_pageState - 1);
		if (m_pageState <= 0) {
			m_pageState = static_cast<Page>(0);
		}
	}
	/// <summary>
	/// オプションページステートの加算
	/// </summary>
	void OptionPageStatePlus()
	{
		m_optionPageState = static_cast<OptionPage>(m_optionPageState + 1);
		if (m_optionPageState >= enOptionPage_Num) {
			m_optionPageState = static_cast<OptionPage>(enOptionPage_Num - 1);
		}
	}
	/// <summary>
	/// オプションページステートの減算
	/// </summary>
	void OptionPageStateMinus()
	{
		m_optionPageState = static_cast<OptionPage>(m_optionPageState - 1);
		if (m_optionPageState <= 0) {
			m_optionPageState = static_cast<OptionPage>(0);
		}
	}
	/// <summary>
	/// メニューステートの加算
	/// </summary>
	void MenuStatePlus()
	{
		m_menuState = static_cast<Menu>(m_menuState + 1);
		if (m_menuState >= enMenu_Num) {
			m_menuState = static_cast<Menu>(enMenu_Num - 1);
		}
	}
	/// <summary>
	/// メニューステートの減算
	/// </summary>
	void MenuStateMinus()
	{
		m_menuState = static_cast<Menu>(m_menuState - 1);
		if (m_menuState <= 0) {
			m_menuState = static_cast<Menu>(0);
		}
	}
	/// <summary>
	/// オブジェクトメニューステートの加算
	/// </summary>
	void ObjMenuStatePlus()
	{
		m_objMenuState = static_cast<ObjMenu>(m_objMenuState + 1);
		if (m_objMenuState >= enObjMenu_Num) {
			m_objMenuState = static_cast<ObjMenu>(enObjMenu_Num - 1);
		}
	}
	/// <summary>
	/// オブジェクトメニューステートの減算
	/// </summary>
	void ObjMenuStateMinus()
	{
		m_objMenuState = static_cast<ObjMenu>(m_objMenuState - 1);
		if (m_objMenuState <= 0) {
			m_objMenuState = static_cast<ObjMenu>(0);
		}
	}
	/// <summary>
	/// オブジェクトステートの加算
	/// </summary>
	void ObjStatePlus()
	{
		m_objState = static_cast<Obj>(m_objState + 1);
		if (m_objState >= enObj_Num) {
			m_objState = static_cast<Obj>(enObj_Num - 1);
		}

	}
	/// <summary>
	/// オブジェクトステートの減算
	/// </summary>
	void ObjStateMinus()
	{
		m_objState = static_cast<Obj>(m_objState - 1);
		if (m_objState <= 0) {
			m_objState = static_cast<Obj>(0);
		}
	}
	/// <summary>
	/// ギミックステートの加算
	/// </summary>
	void GimmickStatePlus()
	{
		m_gimmickState = static_cast<Gimmick>(m_gimmickState + 1);
		if (m_gimmickState >= enGimmick_Num) {
			m_gimmickState = static_cast<Gimmick>(enGimmick_Num - 1);
		}
	}
	/// <summary>
	/// ギミックステートの減算
	/// </summary>
	void GimmickStateMinus()
	{
		m_gimmickState = static_cast<Gimmick>(m_gimmickState - 1);
		if (m_gimmickState <= 0) {
			m_gimmickState = static_cast<Gimmick>(0);
		}
	}
	/// <summary>
	/// 敵ステートの加算
	/// </summary>
	void EnemyStatePlus()
	{
		m_enemyState = static_cast<Enemy>(m_enemyState + 1);
		if (m_enemyState >= enEnemy_Num) {
			m_enemyState = static_cast<Enemy>(enEnemy_Num - 1);
		}
	}
	/// <summary>
	/// 敵ステートの減算
	/// </summary>
	void EnemyStateMinus()
	{
		m_enemyState = static_cast<Enemy>(m_enemyState - 1);
		if (m_enemyState <= 0) {
			m_enemyState = static_cast<Enemy>(0);
		}
	}
	/// <summary>
	/// オプションリストステートの加算
	/// </summary>
	void OptionListStatePlus()
	{
		m_optionListState = static_cast<OptionList>(m_optionListState + 1);
		if (m_optionListState >= enOptionList_Num) {
			m_optionListState = static_cast<OptionList>(enOptionList_Num - 1);
		}
	}
	/// <summary>
	/// オプションリストステートの減算
	/// </summary>
	void OptionListStateMinus()
	{
		m_optionListState = static_cast<OptionList>(m_optionListState - 1);
		if (m_optionListState <= 0) {
			m_optionListState = static_cast<OptionList>(0);
		}
	}
	/// <summary>
	/// ブルームステートの加算
	/// </summary>
	void BloomStatePlus()
	{
		m_bloomState = static_cast<Bloom>(m_bloomState + 1);
		if (m_bloomState >= enBloom_Num) {
			m_bloomState = static_cast<Bloom>(enBloom_Num - 1);
		}
	}
	/// <summary>
	/// ブルームステートの減算
	/// </summary>
	void BloomStateMinus()
	{
		m_bloomState = static_cast<Bloom>(m_bloomState - 1);
		if (m_bloomState <= 0) {
			m_bloomState = static_cast<Bloom>(0);
		}
	}
	/// <summary>
	/// ライトステートの加算
	/// </summary>
	void LightStatePlus()
	{
		m_lightState = static_cast<Light>(m_lightState + 1);
		if (m_lightState >= enLight_Num) {
			m_lightState = static_cast<Light>(enLight_Num - 1);
		}
	}
	/// <summary>
	/// ライトステートの減算
	/// </summary>
	void LightStateMinus()
	{
		m_lightState = static_cast<Light>(m_lightState - 1);
		if (m_lightState <= 0) {
			m_lightState = static_cast<Light>(0);
		}
	}
	/// <summary>
	/// ライトカラーステートの加算
	/// </summary>
	void LightColorStatePlus()
	{
		m_lightColorState = static_cast<LightColor>(m_lightColorState + 1);
		if (m_lightColorState >= enLightColor_Num) {
			m_lightColorState = static_cast<LightColor>(enLightColor_Num - 1);
		}
	}
	/// <summary>
	/// ライトカラーステートの減算
	/// </summary>
	void LightColorStateMinus()
	{
		m_lightColorState = static_cast<LightColor>(m_lightColorState - 1);
		if (m_lightColorState <= 0) {
			m_lightColorState = static_cast<LightColor>(0);
		}
	}
public:
	//ステート取得群
	/// <summary>
	/// ページステートの取得
	/// </summary>
	/// <returns>ページステート</returns>
	Page GetPageState() const
	{
		return m_pageState;
	}
	/// <summary>
	/// オプションページステートの取得
	/// </summary>
	/// <returns>オプションページステート</returns>
	OptionPage GetOptionPageState() const
	{
		return m_optionPageState;
	}
	/// <summary>
	/// メニューステートの取得
	/// </summary>
	/// <returns>メニューステート</returns>
	Menu GetMenuState() const
	{
		return m_menuState;
	}
	/// <summary>
	/// オブジェクトメニューステートの取得
	/// </summary>
	/// <returns>オブジェクトメニューステート</returns>
	ObjMenu GetObjMenuState() const
	{
		return m_objMenuState;
	}
	/// <summary>
	/// オブジェクトステートの取得
	/// </summary>
	/// <returns>オブジェクトステート</returns>
	Obj GetObjState() const
	{
		return m_objState;
	}
	/// <summary>
	/// ギミックステートの取得
	/// </summary>
	/// <returns>ギミックステート</returns>
	Gimmick GetGimmickState() const
	{
		return m_gimmickState;
	}
	/// <summary>
	/// 敵ステートの取得
	/// </summary>
	/// <returns>敵ステート</returns>
	Enemy GetEnemyState() const
	{
		return m_enemyState;
	}
	/// <summary>
	/// オプションリストステートの取得
	/// </summary>
	/// <returns>オプションリストステート</returns>
	OptionList GetOptionListState() const
	{
		return m_optionListState;
	}
	/// <summary>
	/// ブルームステートの取得
	/// </summary>
	/// <returns>ブルームステート</returns>
	Bloom GetBloomState() const
	{
		return m_bloomState;
	}
	/// <summary>
	/// ライトステートの取得
	/// </summary>
	/// <returns>ライトステート</returns>
	Light GetLightState() const
	{
		return m_lightState;
	}
	/// <summary>
	/// ライトカラーステートの取得
	/// </summary>
	/// <returns>ライトカラーステート</returns>
	LightColor GetLightColorState() const
	{
		return m_lightColorState;
	}
};

static inline UIData& GetUIData()
{
	return UIData::GetInstance();
}
