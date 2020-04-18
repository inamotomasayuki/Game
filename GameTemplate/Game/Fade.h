#pragma once

class Fade : public IGameObject
{
public:
	Fade();
	~Fade();
	void Update();
	void Draw() {};
	void DrawFade();
	/// <summary>
	/// アルファ値取得
	/// </summary>
	/// <returns>アルファ値</returns>
	float GetAlpha()
	{
		return m_sprite.GetAlpha();
	}

private:
	Sprite m_sprite;			//スプライト
	CVector3 m_spritePos = CVector3::Zero();			//スプライトの位置
	CQuaternion m_spriteRot = CQuaternion::Identity();	//スプライトの回転
	CVector3 m_spriteScale = CVector3::One();			//スプライトのスケール
	int m_timer = 0;									//タイマー　単位：秒
	bool m_isFade = false;								//フェード中？
};

