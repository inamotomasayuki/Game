#pragma once
class Sky : public IGameObject
{
public:
	Sky();
	~Sky();
	void Update();
	void Draw();
	/// <summary>
	/// À•W‚Ìİ’è
	/// </summary>
	/// <param name="pos">À•W</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ‰ñ“]‚Ìİ’è
	/// </summary>
	/// <param name="rot">‰ñ“]</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// Šg‘å—¦‚Ìİ’è
	/// </summary>
	/// <param name="scale">Šg‘å—¦</param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}
private:
	SkinModel m_skinModel;								//ƒXƒLƒ“ƒ‚ƒfƒ‹
	CVector3 m_position = CVector3::Zero();				//À•W
	CQuaternion m_rotation = CQuaternion::Identity();	//‰ñ“]
	CVector3 m_scale = CVector3::One();					//Šg‘å—¦

};

