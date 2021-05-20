#pragma once
namespace {
	const float INIT_COLOR_R = 0.4f;		//R�̏����l
	const float INIT_COLOR_G = 0.4f;		//G�̏����l
	const float INIT_COLOR_B = 0.4f;		//B�̏����l
	const int COUNT_MAX = 100;				//�J�E���g�ő�l
	const int COUNT_MIN = 0;				//�J�E���g�ŏ��l
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
	/// �u���[���̃s�N�Z���L������P�x�̉��Z
	/// </summary>
	/// <param name="lum">���Z����P�x</param>
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
	/// �u���[���̋����̉��Z
	/// </summary>
	/// <param name="pow">���Z����u���[���̋���</param>
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
	/// �f�B���N�V�������C�g�̃J���[�̐ݒ�
	/// </summary>
	/// <param name="color">�ݒ肷��J���[</param>
	void SetColor(const CVector4& color)
	{
		m_color = color;
	}
	/// <summary>
	/// R�����̉��Z
	/// </summary>
	/// <param name="r">R����</param>
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
	/// G�����̉��Z
	/// </summary>
	/// <param name="g">G����</param>
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
	/// B�����̉��Z
	/// </summary>
	/// <param name="b">B����</param>
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
	/// ���邳�̉��Z
	/// </summary>
	/// <param name="brightness">���邳</param>
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
	/// ��̖��邳�̉��Z
	/// </summary>
	/// <param name="skyBrightness">���邳</param>
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
	/// �u���[���̃s�N�Z���L������P�x�̎擾
	/// </summary>
	/// <returns></returns>
	float GetLuminance() const
	{
		return m_lum;
	}
	/// <summary>
	/// �u���[���̋����̎擾
	/// </summary>
	/// <returns>�u���[���̋���</returns>
	float GetBloomPow() const
	{
		return m_pow;
	}
	/// <summary>
	/// �f�B���N�V�������C�g�̃J���[�̎擾
	/// </summary>
	/// <returns>�f�B���N�V�������C�g�̃J���[</returns>
	const CVector4& GetColor() const
	{
		return m_color;
	}
	/// <summary>
	/// R�����̎擾
	/// </summary>
	/// <returns>R����</returns>
	float GetColorR() const
	{
		return m_colorR;
	}
	/// <summary>
	/// R�����̃J�E���g�擾
	/// </summary>
	/// <returns>R�����̃J�E���g</returns>
	float GetCountColorR() const
	{
		return m_countColorR;
	}
	/// <summary>
	/// G�����̎擾
	/// </summary>
	/// <returns>G����</returns>
	float GetColorG() const
	{
		return m_colorG;
	}
	/// <summary>
	/// G�����̃J�E���g�擾
	/// </summary>
	/// <returns>G�����̃J�E���g</returns>
	float GetCountColorG() const
	{
		return m_countColorG;
	}
	/// <summary>
	/// B�����̎擾
	/// </summary>
	/// <returns>B����</returns>
	float GetColorB() const
	{
		return m_colorB;
	}
	/// <summary>
	/// B�����̃J�E���g�擾
	/// </summary>
	/// <returns>B�����̃J�E���g</returns>
	float GetCountColorB() const
	{
		return m_countColorB;
	}
	/// <summary>
	/// �P�x�J�E���g�̎擾
	/// </summary>
	/// <returns>�P�x�J�E���g</returns>
	int GetLumCount() const
	{
		return m_lumCount;
	}
	/// <summary>
	/// �����J�E���g�̎擾
	/// </summary>
	/// <returns>�����J�E���g</returns>
	int GetPowCount() const
	{
		return m_powCount;
	}
	/// <summary>
	/// ���邳�̎擾
	/// </summary>
	/// <returns>���邳</returns>
	float GetBrightness() const
	{
		return m_brightness;
	}
	/// <summary>
	/// ���邳�J�E���g�̎擾
	/// </summary>
	/// <returns>���邳�J�E���g</returns>
	float GetBrightnessCount() const
	{
		return m_brightnessCount;
	}
	/// <summary>
	/// ��̖��邳�擾
	/// </summary>
	/// <returns>��̖��邳</returns>
	float GetSkyBrightness() const
	{
		return m_skyBrightness;
	}
	/// <summary>
	/// ��̖��邳�J�E���g�̎擾
	/// </summary>
	/// <returns>��̖��邳�J�E���g</returns>
	float GetSkyBrightnessCount() const
	{
		return m_skyBrightnessCount;
	}
	/// <summary>
	/// �e�u���[���p�����[�^�̏�����
	/// </summary>
	void InitBloomParameter()
	{
		m_lum = 1.001f;
		m_lumCount = 50;
		m_pow = 4.0f;
		m_powCount = 50;
	}
	/// <summary>
	/// �e���C�g�p�����[�^������
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
	float m_lum = 1.001f;				//�u���[���̃s�N�Z���L������P�x�̋���
	float m_lumCount = 50.0f;			//��L�̃J�E���g
	float m_pow = 4.0f;					//�u���[���̋���
	float m_powCount = 50.0f;			//��L�̃J�E���g
	CVector4 m_color = { INIT_COLOR_R,INIT_COLOR_G,INIT_COLOR_B,1.0f };		//�f�B���N�V�������C�g�̃J���[
	float m_colorR = INIT_COLOR_R;		//R
	float m_countColorR = 50.0f;		//R�J�E���g
	float m_colorG = INIT_COLOR_G;		//G
	float m_countColorG = 50.0f;		//G�J�E���g
	float m_colorB = INIT_COLOR_B;		//B
	float m_countColorB = 50.0f;		//B�J�E���g
	float m_brightness = 1.5f;			//���邳
	float m_brightnessCount = 50.0f;	//���邳�J�E���g
	float m_skyBrightness = 0.8f;		//��̖��邳
	float m_skyBrightnessCount = 30.0f;	//��̖��邳�J�E���g
};

static inline OptionData& GetOptionData()
{
	return OptionData::GetInstance();
}
