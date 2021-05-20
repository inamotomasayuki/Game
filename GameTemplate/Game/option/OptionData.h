#pragma once
namespace {
	const float INIT_COLOR_R = 0.4f;		//Rの初期値
	const float INIT_COLOR_G = 0.4f;		//Gの初期値
	const float INIT_COLOR_B = 0.4f;		//Bの初期値
	const int COUNT_MAX = 100;				//カウント最大値
	const int COUNT_MIN = 0;				//カウント最小値
	const int COUNT_HALF = 50;
}
class OptionData final
{
public:
	static OptionData& GetInstance()
	{
		static OptionData instance;
		return instance;
	}
	/// <summary>
	/// ブルームのピクセルキルする輝度の加算
	/// </summary>
	/// <param name="lum">加算する輝度</param>
	void AddLuminance(float lum)
	{
		if (m_lumCount >= COUNT_MIN && m_lumCount <= COUNT_MAX) {
			m_lum += lum;
			float f = 1 / lum;
			if (lum < 0) {
				lum = lum * -1;
			}
			m_lumCount -= lum * f;
			if (m_lumCount <= COUNT_MIN) {
				m_lum = 1.001f + lum * 50;
				m_lumCount = COUNT_MIN;
			}
			if (m_lumCount >= COUNT_MAX) {
				m_lum = 1.001f - lum * 50;
				m_lumCount = COUNT_MAX;
			}
		}
	}
	/// <summary>
	/// ブルームの強さの加算
	/// </summary>
	/// <param name="pow">加算するブルームの強さ</param>
	void AddPow(float pow)
	{
		if (m_powCount >= COUNT_MIN && m_powCount <= COUNT_MAX) {
			m_pow += pow;
			float f = 1 / pow;
			if (pow < 0) {
				pow = pow * -1;
			}
			m_powCount -= pow * f;
			if (m_powCount <= COUNT_MIN) {
				m_pow = 4.0f + pow * 50;
				m_powCount = COUNT_MIN;
			}
			if (m_powCount >= COUNT_MAX) {
				m_pow = 4.0f - pow * 50;
				m_powCount = COUNT_MAX;
			}
		}
	}
	/// <summary>
	/// ディレクションライトのカラーの設定
	/// </summary>
	/// <param name="color">設定するカラー</param>
	void SetColor(const CVector4& color)
	{
		m_color = color;
	}
	/// <summary>
	/// R成分の加算
	/// </summary>
	/// <param name="r">R成分</param>
	void AddColorR(float r)
	{
		if (m_countColorR >= COUNT_MIN && m_countColorR <= COUNT_MAX) {
			m_colorR += r;
			float f = 1 / r;
			if (r < 0) {
				r = r * -1;
			}
			m_countColorR += r * f;
			if (m_countColorR <= COUNT_MIN) {
				m_colorR = INIT_COLOR_R - r * 50;
				m_countColorR = COUNT_MIN;
			}
			if (m_countColorR >= COUNT_MAX) {
				m_colorR = INIT_COLOR_R + r * 50;
				m_countColorR = COUNT_MAX;
			}
		}
	}
	/// <summary>
	/// G成分の加算
	/// </summary>
	/// <param name="g">G成分</param>
	void AddColorG(float g)
	{
		if (m_countColorG >= COUNT_MIN && m_countColorG <= COUNT_MAX) {
			m_colorG += g;
			float f = 1 / g;
			if (g < 0) {
				g = g * -1;
			}
			m_countColorG += g * f;
			if (m_countColorG <= COUNT_MIN) {
				m_colorG = INIT_COLOR_G - g * 50;
				m_countColorG = COUNT_MIN;
			}
			if (m_countColorG >= COUNT_MAX) {
				m_colorG = INIT_COLOR_G + g * 50;
				m_countColorG = COUNT_MAX;
			}
		}
	}
	/// <summary>
	/// B成分の加算
	/// </summary>
	/// <param name="b">B成分</param>
	void AddColorB(float b)
	{
		if (m_countColorB >= COUNT_MIN && m_countColorB <= COUNT_MAX) {
			m_colorB += b;
			float f = 1 / b;
			if (b < 0) {
				b = b * -1;
			}
			m_countColorB += b * f;
			if (m_countColorB <= COUNT_MIN) {
				m_colorB = INIT_COLOR_B - b * 50;
				m_countColorB = COUNT_MIN;
			}
			if (m_countColorB >= COUNT_MAX) {
				m_colorB = INIT_COLOR_B + b * 50;
				m_countColorB = COUNT_MAX;
			}
		}
	}
	/// <summary>
	/// 明るさの加算
	/// </summary>
	/// <param name="brightness">明るさ</param>
	void AddBrightness(float brightness)
	{
		if (m_brightnessCount >= COUNT_MIN && m_brightnessCount <= COUNT_MAX) {
			m_brightness += brightness;
			float f = 1 / brightness;
			if (brightness < 0) {
				brightness = brightness * -1;
			}
			m_brightnessCount += brightness * f;
			if (m_brightnessCount <= COUNT_MIN) {
				m_brightness = 1.5f - brightness * 50;
				m_brightnessCount = COUNT_MIN;
			}
			if (m_brightnessCount >= COUNT_MAX) {
				m_brightness = 1.5f + brightness * 50;
				m_brightnessCount = COUNT_MAX;
			}
		}
	}
	/// <summary>
	/// 空の明るさの加算
	/// </summary>
	/// <param name="skyBrightness">明るさ</param>
	void AddSkyBrightness(float skyBrightness)
	{
		if (m_skyBrightnessCount >= COUNT_MIN && m_skyBrightnessCount <= COUNT_MAX) {
			m_skyBrightness += skyBrightness;
			float f = 1 / skyBrightness;
			if (skyBrightness < 0) {
				skyBrightness = skyBrightness * -1;
			}
			m_skyBrightnessCount += skyBrightness * f;
			if (m_skyBrightnessCount <= COUNT_MIN) {
				m_skyBrightness = 0.8f - skyBrightness * 30;
				m_skyBrightnessCount = COUNT_MIN;
			}
			if (m_skyBrightnessCount >= COUNT_MAX) {
				m_skyBrightness = 0.8f + skyBrightness * 70;
				m_skyBrightnessCount = COUNT_MAX;
			}
		}
	}
	/// <summary>
	/// ブルームのピクセルキルする輝度の取得
	/// </summary>
	/// <returns></returns>
	float GetLuminance() const
	{
		return m_lum;
	}
	/// <summary>
	/// ブルームの強さの取得
	/// </summary>
	/// <returns>ブルームの強さ</returns>
	float GetBloomPow() const
	{
		return m_pow;
	}
	/// <summary>
	/// ディレクションライトのカラーの取得
	/// </summary>
	/// <returns>ディレクションライトのカラー</returns>
	const CVector4& GetColor() const
	{
		return m_color;
	}
	/// <summary>
	/// R成分の取得
	/// </summary>
	/// <returns>R成分</returns>
	float GetColorR() const
	{
		return m_colorR;
	}
	/// <summary>
	/// R成分のカウント取得
	/// </summary>
	/// <returns>R成分のカウント</returns>
	float GetCountColorR() const
	{
		return m_countColorR;
	}
	/// <summary>
	/// G成分の取得
	/// </summary>
	/// <returns>G成分</returns>
	float GetColorG() const
	{
		return m_colorG;
	}
	/// <summary>
	/// G成分のカウント取得
	/// </summary>
	/// <returns>G成分のカウント</returns>
	float GetCountColorG() const
	{
		return m_countColorG;
	}
	/// <summary>
	/// B成分の取得
	/// </summary>
	/// <returns>B成分</returns>
	float GetColorB() const
	{
		return m_colorB;
	}
	/// <summary>
	/// B成分のカウント取得
	/// </summary>
	/// <returns>B成分のカウント</returns>
	float GetCountColorB() const
	{
		return m_countColorB;
	}
	/// <summary>
	/// 輝度カウントの取得
	/// </summary>
	/// <returns>輝度カウント</returns>
	int GetLumCount() const
	{
		return m_lumCount;
	}
	/// <summary>
	/// 強さカウントの取得
	/// </summary>
	/// <returns>強さカウント</returns>
	int GetPowCount() const
	{
		return m_powCount;
	}
	/// <summary>
	/// 明るさの取得
	/// </summary>
	/// <returns>明るさ</returns>
	float GetBrightness() const
	{
		return m_brightness;
	}
	/// <summary>
	/// 明るさカウントの取得
	/// </summary>
	/// <returns>明るさカウント</returns>
	float GetBrightnessCount() const
	{
		return m_brightnessCount;
	}
	/// <summary>
	/// 空の明るさ取得
	/// </summary>
	/// <returns>空の明るさ</returns>
	float GetSkyBrightness() const
	{
		return m_skyBrightness;
	}
	/// <summary>
	/// 空の明るさカウントの取得
	/// </summary>
	/// <returns>空の明るさカウント</returns>
	float GetSkyBrightnessCount() const
	{
		return m_skyBrightnessCount;
	}
	/// <summary>
	/// 各ブルームパラメータの初期化
	/// </summary>
	void InitBloomParameter()
	{
		m_lum = 1.001f;
		m_lumCount = 50;
		m_pow = 4.0f;
		m_powCount = 50;
	}
	/// <summary>
	/// 各ライトパラメータ初期化
	/// </summary>
	void InitLightParameter()
	{
		m_color = { INIT_COLOR_R,INIT_COLOR_G,INIT_COLOR_B,1.0f };
		m_colorR = INIT_COLOR_R;
		m_colorG = INIT_COLOR_G;
		m_colorB = INIT_COLOR_B;
		m_countColorR = 50;
		m_countColorG = 50;
		m_countColorB = 50;
		m_brightness = 1.5f;
		m_brightnessCount = 50;
		m_skyBrightness = 0.8f;
		m_skyBrightnessCount = 30;
	}
private:
	float m_lum = 1.001f;				//ブルームのピクセルキルする輝度の強さ
	float m_lumCount = 50.0f;			//上記のカウント
	float m_pow = 4.0f;					//ブルームの強さ
	float m_powCount = 50.0f;			//上記のカウント
	CVector4 m_color = { INIT_COLOR_R,INIT_COLOR_G,INIT_COLOR_B,1.0f };		//ディレクションライトのカラー
	float m_colorR = INIT_COLOR_R;		//R
	float m_countColorR = 50.0f;		//Rカウント
	float m_colorG = INIT_COLOR_G;		//G
	float m_countColorG = 50.0f;		//Gカウント
	float m_colorB = INIT_COLOR_B;		//B
	float m_countColorB = 50.0f;		//Bカウント
	float m_brightness = 1.5f;			//明るさ
	float m_brightnessCount = 50.0f;	//明るさカウント
	float m_skyBrightness = 0.8f;		//空の明るさ
	float m_skyBrightnessCount = 30.0f;	//空の明るさカウント
};

static inline OptionData& GetOptionData()
{
	return OptionData::GetInstance();
}
