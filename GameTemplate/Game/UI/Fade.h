#pragma once

class Fade final : public IGameObject
{
public:
	Fade();
	~Fade();
	void Update() override;
	void Draw() override {};
	void DrawFade() override;
	/// <summary>
	/// �A���t�@�l�擾
	/// </summary>
	/// <returns>�A���t�@�l</returns>
	float GetAlpha() const
	{
		return m_sprite.GetAlpha();
	}

private:
	Sprite m_sprite;			//�X�v���C�g
	CVector3 m_spritePos = CVector3::Zero();			//�X�v���C�g�̈ʒu
	CQuaternion m_spriteRot = CQuaternion::Identity();	//�X�v���C�g�̉�]
	CVector3 m_spriteScale = CVector3::One();			//�X�v���C�g�̃X�P�[��
	int m_timer = 0;									//�^�C�}�[�@�P�ʁF�b
	bool m_isFade = false;								//�t�F�[�h���H
};

